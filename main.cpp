/* main.cpp */

// Include *
#include <cstdio>
#include <iostream>
#include <fstream>
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
#include "geometric/hermiteSpline.h"
#include "geometric/polygon.h"
#include "geometric/splineFactory.h"
#include "geometric/wireframe.h"
#include "math/constant.h"
#include "math/linearOperator.h"
#include "math/polynomial.h"
#include "render/screenRenderer.h"
#include "render/viewport.h"
#include "render/window.h"
#include "render/clipping/cohenSutherland.h"
#include "render/clipping/tridimensional.h"
#include "render/projection/projector.h"
#include "render/projection/parallel.h"
#include "render/projection/perspective.h"
#include "test/lib/testList.h"
#include "view/pixel.h"
#include "view/SDLScreen.h"

using namespace Math;
using std::vector;

constexpr int D = 3; // Número de dimensões em que o programa trabalha.

void waitEnter() {
    SDL_Event e;
    while( true )
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                if( e.key.keysym.sym == SDLK_RETURN )
                    goto melga;

melga: return;
}

void clear( Drawable& d, DisplayFile<D>& df, ScreenRenderer<D>& renderer ) {
    //GAMBIARRRRRA
    d.setColor( 255, 255, 255, 255 );
    for( int i = 0; i < d.width(); i++ )
        for( int j = 0; j < d.height(); j++ )
            d.paint({ i, j });
    d.setColor( 0, 0, 0, 255 );
    df.draw( &renderer );
    d.update();
}

int main( int argc, char * argv[] ) {
    if( !Test::run() )
        return 1;

    SDLScreen sdl( 600, 600, "Teste" );
    Window<D> w;
    Viewport v = Viewport::generateViewport( &sdl );
    v.xmin += 10;
    v.ymin += 10;
    v.xmax -= 10;
    v.ymax -= 10;
    Projector<D> p = parallel<D>;
    PreLineClipper<D> ct = tridimensional;
    PostLineClipper cs = CohenSutherland;
    ScreenRenderer<D> renderer( v, w, p, ct, cs, sdl );
    DisplayFile<D> df;

    bool hold = false;
    auto update = [&sdl, &df, &renderer, &hold](){ 
        if( !hold )
            clear(sdl, df, renderer);
        else
            hold = false;
    }; // hold barrará atualizações na visualização do mundo.
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
            [&w, &update] () {
                w.setCenter({1, 1, 1});
                w.setWidth(2.0);
                w.setHeight(2.0);
                w.setDistance(1.0);
                w.setFront({-1, -1, -1});
                w.setUp({-1, 2, -1});
                update();
            } ) );
    bash.addCommand( "hold", CommandFactory::makeFunctional(
            [&hold](){ hold = true; } ) );

    /* add <command> */
    CommandMultiplexer * add = new CommandMultiplexer();
    bash.addCommand( "add", add );

    add->addCommand( "point", CommandFactory::makeFunctional( 
            [&df, &update]( std::string name, Math::Point<D> p ) {
                df.addObject( name, new DrawablePoint<D>( p ) );
                update();
            } ) );
    add->addCommand( "bezier", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<D>> v ) {
                df.addObject( name, new BezierSpline<D>( v ) );
                update();
            } ) );
    add->addCommand( "bspline", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<D>> v ) {
                df.addObject( name, new BSpline<D>( v ) );
                update();
            } ) );
    add->addCommand( "polygon", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<D>> v ) {
                df.addObject( name, new Polygon<D>( v ) );
                update();
            } ) );
    add->addCommand( "wireframe", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, std::vector<Math::Point<D>> v,
                std::vector<std::pair<int, int>> e )
            {
                df.addObject( name, new Wireframe<D>( v, e ) );
                update();
            } ) );

    /* add cubic <command> */
    CommandMultiplexer * cubic = new CommandMultiplexer();
    add->addCommand( "cubic", cubic );

    cubic->addCommand( "bezier", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, Math::Point<D> p1,
                Math::Point<D> p2, Math::Point<D> p3, Math::Point<D> p4 )
            {
                CubicSpline<D> * spline = new CubicSpline<D>(
                    SplineFactory::Bezier<D>( p1, p2, p3, p4 ) );
                df.addObject( name, spline );
                update();
            } ) );
    cubic->addCommand( "hermite", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, Math::Point<D> p1,
                Math::Vector<D> r1, Math::Point<D> p4, Math::Vector<D> r4 )
            {
                CubicSpline<D> * spline = new CubicSpline<D>(
                    SplineFactory::Hermite<D>( p1, r1, p4, r4 ) );
                df.addObject( name, spline );
                update();
            } ) );
    cubic->addCommand( "bspline", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, Math::Point<D> p0,
                Math::Point<D> p1, Math::Point<D> p2, Math::Point<D> p3 )
            {
                CubicSpline<D> * spline = new CubicSpline<D>(
                    SplineFactory::BSpline<D>( p0, p1, p2, p3 ) );
                df.addObject( name, spline );
                update();
            } ) );

    /* move <command> */
    CommandMultiplexer * move = new CommandMultiplexer();
    bash.addCommand( "move", move );

    move->addCommand( "up", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::Translation<D>( {0, amount, 0} ) );
                update();
            } ) );
    move->addCommand( "down", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::Translation<D>( {0, -amount, 0} ) );
                update();
            } ) );
    move->addCommand( "left", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::Translation<D>( {-amount, 0, 0} ) );
                update();
            } ) );
    move->addCommand( "right", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::Translation<D>( {amount, 0, 0} ) );
                update();
            } ) );
    move->addCommand( "front", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::Translation<D>( {0, 0, amount} ) );
                update();
            } ) );
    move->addCommand( "back", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double amount ) {
                df.transform( name, 
                    LinearFactory::Translation<D>( {0, 0, -amount} ) );
                update();
            } ) );

    /* move window <command> */
    CommandMultiplexer * moveWindow = new CommandMultiplexer();
    move->addCommand( "window", moveWindow );

    moveWindow->addCommand( "vector", CommandFactory::makeFunctional(
            [&w, &update]( Math::Vector<3> v ) {
                w.move( v );
                update();
            } ) );
    moveWindow->addCommand( "front", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.moveFront( d );
                update();
            } ) );
    moveWindow->addCommand( "back", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.moveFront( -d );
                update();
            } ) );
    moveWindow->addCommand( "up", CommandFactory::makeFunctional(
            [&w, &update]( double amount ) {
                w.moveUp( amount );
                update();
            } ) );
    moveWindow->addCommand( "down", CommandFactory::makeFunctional(
            [&w, &update]( double amount ) {
                w.moveUp( -amount );
                update();
            } ) );
    moveWindow->addCommand( "left", CommandFactory::makeFunctional(
            [&w, &update]( double amount ) {
                w.moveLeft( amount );
                update();
            } ) );
    moveWindow->addCommand( "right", CommandFactory::makeFunctional(
            [&w, &update]( double amount ) {
                w.moveLeft( -amount );
                update();
            } ) );

    /* rotate <command> */
    CommandMultiplexer * rotate = new CommandMultiplexer();
    bash.addCommand( "rotate", rotate );

    rotate->addCommand( "origin", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double degrees,
                Math::Vector<D> axis ) 
            {
                df.transform( name, LinearFactory::Rotation3D(
                        degrees/180*Math::PI, axis ) );
                update();
            } ) );
    rotate->addCommand( "point", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double degrees, 
                Math::Vector<D> v, Math::Point<D> p ) 
            {
                df.transform( name, 
                    LinearFactory::Rotation3D( degrees/180*Math::PI, v, p ) );
                update();
            } ) );
    rotate->addCommand( "center", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double degrees, 
                Math::Vector<D> axis )
            {
                df.center( name );
                df.transform( name, LinearFactory::Rotation3D(
                        degrees/180*Math::PI, axis, df.center( name ) ) );
                update();
            } ) );

    /* rotate window <command> */
    CommandMultiplexer * rotateWindow = new CommandMultiplexer();
    rotate->addCommand( "window", rotateWindow );

    rotateWindow->addCommand( "up", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.rotateUp( d/180*Math::PI );
                update();
            } ) );
    rotateWindow->addCommand( "down", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.rotateUp( -d/180*Math::PI );
                update();
            } ) );
    rotateWindow->addCommand( "left", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.rotateLeft( d/180*Math::PI );
                update();
            } ) );
    rotateWindow->addCommand( "right", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.rotateLeft( -d/180*Math::PI );
                update();
            } ) );
    rotateWindow->addCommand( "clock", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.rotateClockwise( d/180*Math::PI );
                update();
            } ) );
    rotateWindow->addCommand( "counterclock", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.rotateClockwise( -d/180*Math::PI );
                update();
            } ) );


    /* zoom <in/out> */
    CommandMultiplexer * zoom = new CommandMultiplexer();
    bash.addCommand( "zoom", zoom );
    
    zoom->addCommand( "in", CommandFactory::makeFunctional(
            [&w, &update]( double percent ) {
                w.vscale( 1 - percent/100 );
                w.hscale( 1 - percent/100 );
                update();
            } ) );
    zoom->addCommand( "out", CommandFactory::makeFunctional(
            [&w, &update]( double percent ) {
                w.vscale( 1 + percent/100 );
                w.hscale( 1 + percent/100 );
                update();
            } ) );
    zoom->addCommand( "distance", CommandFactory::makeFunctional(
            [&w, &update]( double d ) {
                w.dscale( d );
                update();
            } ) );


    bash.addCommand( "scale", CommandFactory::makeFunctional(
            [&df, &update]( std::string name, double factor ) {
                df.transform( name, LinearFactory::Scale<D>(
                        factor, df.center( name ) ) );
                update();
            } ) );

    bash.addCommand( "delete", CommandFactory::makeFunctional(
            [&df, &update]( std::string name ) {
                df.remove( name );
                update();
            } ) );

    /* set <parallel/perspective> */
    CommandMultiplexer * set = new CommandMultiplexer();
    bash.addCommand( "set", set );

    set->addCommand( "parallel", CommandFactory::makeFunctional(
            [&renderer, &update]() {
                renderer.setProjector( parallel<D> );
                update();
            } ) );
    set->addCommand( "perspective", CommandFactory::makeFunctional(
            [&renderer, &update]() {
                renderer.setProjector( perspective );
                update();
            } ) );

    if( argc == 1 )
        bash.readFrom( std::cin );
    else {
        std::ifstream file( argv[1] );
        bash.readFrom( file );
    }

    return 0;
}
