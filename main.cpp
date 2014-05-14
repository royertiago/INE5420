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

    /* add cubic <chosen cubic> */
    CommandMultiplexer * cubic = new CommandMultiplexer();
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

    /* add <chosen object> */
    CommandMultiplexer * add = new CommandMultiplexer();
    add->addCommand( "cubic", cubic );
    add->addCommand( "point", CommandFactory::makeFunctional( 
            [&df, &update]( std::string name, Math::Point<2> p ) {
                df.addObject( name, new DrawablePoint( p ) );
                update();
            } ) );

    bash.addCommand( "add", add );

    bash.readFrom( std::cin );

    return 0;
}
