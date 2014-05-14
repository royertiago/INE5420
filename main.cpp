/* main.cpp */

// Include *
#include <cstdio>
#include <iostream>
#include <vector>
#include <SDL.h>
#include "displayFile.h"
#include "parseVector.h"
#include "command/shell.h"
#include "command/commandFactory.h"
#include "command/commandMultiplexer.h"
#include "geometric/bezierSpline.h"
#include "geometric/BSpline.h"
#include "geometric/cubicSpline.h"
#include "geometric/drawablePoint.h"
#include "geometric/geometricFactory.h"
#include "geometric/hermiteSpline.h"
#include "geometric/polygon.h"
#include "geometric/splineFactory.h"
#include "math/constant.h"
#include "math/linearOperator.h"
#include "math/polynomial.h"
#include "render/screenRenderer.h"
#include "render/viewport.h"
#include "render/viewportTransform.h"
#include "render/window.h"
#include "render/windowTransform.h"
#include "render/clipping/clippingArea.h"
#include "render/clipping/cohenSutherland.h"
#include "test/lib/testList.h"
#include "view/pixel.h"
#include "view/SDLScreen.h"

using namespace Math;
using std::vector;

void waitEnter() {
    SDL_Event e;
    while( true )
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                if( e.key.keysym.sym == SDLK_RETURN )
                    goto melga;

melga: return;
}

void clear( Drawable& d, DisplayFile<2>& df, ScreenRenderer& renderer ) {
    //GAMBIARRRRRA
    d.setColor( 255, 255, 255, 255 );
    for( int i = 0; i < d.width(); i++ )
        for( int j = 0; j < d.height(); j++ )
            d.paint({ i, j });
    d.setColor( 0, 0, 0, 255 );
    df.draw( &renderer );
    d.update();
}

int main() {
    if( !Test::run() )
        return 1;

    SDLScreen sdl( 600, 600, "Teste" );
    WindowTransform wt( ClippingArea::normalized );
    Viewport v = Viewport::generateViewport( &sdl );
    v.xmin += 10;
    v.ymin += 10;
    v.xmax -= 10;
    v.ymax -= 10;
    CohenSutherland cs( ClippingArea::normalized );
    ScreenRenderer renderer( v, wt, cs, sdl );
    DisplayFile<2> df;
    auto update = [&sdl, &df, &renderer](){ clear(sdl, df, renderer); };
    update();

    Shell bash;
    bash.addCommand( "#",    CommandFactory::nop() ); // comentário
    bash.addCommand( "echo", CommandFactory::echo() );
    bash.addCommand( "load", CommandFactory::load() );

    bash.addCommand( "clear", CommandFactory::makeFunctional(
            [&df, &update] () {
                df.clear();
                update();
            } ) );
    bash.addCommand( "reset", CommandFactory::makeFunctional(
            [&wt, &update] () {
                wt.window().x = 0.5;
                wt.window().y = 0.5;
                wt.window().w = 1.0;
                wt.window().h = 1.0;
                wt.window().t = 0.0;
                update();
            } ) );

    /* add <command> */
    CommandMultiplexer * add = new CommandMultiplexer();
    bash.addCommand( "add", add );

    add->addCommand( "point", CommandFactory::makeFunctional( 
            [&df, &update]( std::string name, Math::Point<2> p ) {
                df.addObject( name, new DrawablePoint( p ) );
                update();
            } ) );
    add->addCommand( "bezier", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<2>> v ) {
                df.addObject( name, new BezierSpline<2>( v ) );
                update();
            } ) );
    add->addCommand( "bspline", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<2>> v ) {
                df.addObject( name, new BSpline<2>( v ) );
                update();
            } ) );
    add->addCommand( "polygon", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<2>> v ) {
                Math::Point<2>* p = new Math::Point<2>[v.size()];
                for( int i = 0; i < v.size(); ++i )
                    p[i] = v[i];

                df.addObject( name, new Polygon( p, v.size() ) );
                update();
            } ) );

    /* add cubic <command> */
    CommandMultiplexer * cubic = new CommandMultiplexer();
    add->addCommand( "cubic", cubic );

    cubic->addCommand( "bezier", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, Math::Point<2> p1,
                Math::Point<2> p2, Math::Point<2> p3, Math::Point<2> p4 )
            {
                CubicSpline<2> * spline = new CubicSpline<2>(
                    SplineFactory::Bezier<2>( p1, p2, p3, p4 ) );
                df.addObject( name, spline );
                update();
            } ) );
    cubic->addCommand( "hermite", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, Math::Point<2> p1,
                Math::Vector<2> r1, Math::Point<2> p4, Math::Vector<2> r4 )
            {
                CubicSpline<2> * spline = new CubicSpline<2>(
                    SplineFactory::Hermite<2>( p1, r1, p4, r4 ) );
                df.addObject( name, spline );
                update();
            } ) );
    cubic->addCommand( "bspline", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, Math::Point<2> p0,
                Math::Point<2> p1, Math::Point<2> p2, Math::Point<2> p3 )
            {
                CubicSpline<2> * spline = new CubicSpline<2>(
                    SplineFactory::BSpline<2>( p0, p1, p2, p3 ) );
                df.addObject( name, spline );
                update();
            } ) );

    /* move <command> */
    CommandMultiplexer * move = new CommandMultiplexer();
    bash.addCommand( "move", move );

    move->addCommand( "up", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::make2DTranslation( {0, amount} ) );
                update();
            } ) );
    move->addCommand( "down", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::make2DTranslation( {0, -amount} ) );
                update();
            } ) );
    move->addCommand( "left", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::make2DTranslation( {-amount, 0} ) );
                update();
            } ) );
    move->addCommand( "right", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::make2DTranslation( {amount, 0} ) );
                update();
            } ) );

    /* move window <command> */
    CommandMultiplexer * moveWindow = new CommandMultiplexer();
    move->addCommand( "window", moveWindow );

    moveWindow->addCommand( "up", CommandFactory::makeFunctional(
            [&wt, &update]( double amount ) {
                wt.window().moveUp( {0, amount} );
                update();
            } ) );
    moveWindow->addCommand( "down", CommandFactory::makeFunctional(
            [&wt, &update]( double amount ) {
                wt.window().moveUp( {0, -amount} );
                update();
            } ) );
    moveWindow->addCommand( "left", CommandFactory::makeFunctional(
            [&wt, &update]( double amount ) {
                wt.window().moveUp( {-amount, 0} );
                update();
            } ) );
    moveWindow->addCommand( "right", CommandFactory::makeFunctional(
            [&wt, &update]( double amount ) {
                wt.window().moveUp( {amount, 0} );
                update();
            } ) );

    /* rotate <command> */
    CommandMultiplexer * rotate = new CommandMultiplexer();
    bash.addCommand( "rotate", rotate );

    rotate->addCommand( "origin", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double degrees ) {
                df.transform( name, LinearFactory::make2DRotation(
                        degrees/180*Math::PI ) );
                update();
            } ) );
    rotate->addCommand( "point", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double degrees, 
                Math::Point<2> p ) 
            {
                df.transform( name, 
                    LinearFactory::make2DRotation( degrees/180*Math::PI, p ) );
                update();
            } ) );
    rotate->addCommand( "center", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double degrees ) {
                df.transform( name, LinearFactory::make2DRotation(
                        degrees/180*Math::PI, df.center( name ) ) );
                update();
            } ) );
    rotate->addCommand( "window", CommandFactory::makeFunctional(
            [&wt, &update]( double degrees ) {
                wt.window().rotate( degrees/180*Math::PI );
                update();
            } ) );


    /* zoom <in/out> */
    CommandMultiplexer * zoom = new CommandMultiplexer();
    bash.addCommand( "zoom", zoom );
    
    zoom->addCommand( "in", CommandFactory::makeFunctional(
            [&wt, &update]( double percent ) {
                wt.window().vscale( 1 - percent/100 );
                wt.window().hscale( 1 - percent/100 );
                update();
            } ) );
    zoom->addCommand( "out", CommandFactory::makeFunctional(
            [&wt, &update]( double percent ) {
                wt.window().vscale( 1 + percent/100 );
                wt.window().hscale( 1 + percent/100 );
                update();
            } ) );


    bash.addCommand( "scale", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double factor ) {
                df.transform( name, LinearFactory::make2DScale(
                        factor, df.center( name ) ) );
                update();
            } ) );

    bash.addCommand( "delete", CommandFactory::makeFunctional(
            [&df, &update]( std::string name ) {
                df.remove( name );
                update();
            } ) );

    bash.readFrom( std::cin );

    return 0;
}
