/* main.cpp */

// Include *
#include <cstdio>
#include <vector>
#include <SDL.h>
#include "displayFile.h"
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

void clear( Drawable& d, DisplayFile& df, ScreenRenderer& renderer ) {
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
    DisplayFile df;

    HermiteSpline<2> * h = new HermiteSpline<2>(
            {{ 0.25, 0.25},
             { 0.75, 0.75}},
            {{ 0.75, 0.25},
             { 0.75, 0.75}} );

    df.addObject( h );
    clear( sdl, df, renderer );
    waitEnter();

    h->addPoint( {0.5, 0.5}, {0.0, 1.0} );
    clear( sdl, df, renderer );
    waitEnter();

    h->addPoint( {0.2, 0.5}, {0.0, -1.0} );
    clear( sdl, df, renderer );
    waitEnter();

    h->addPoint( {0.8, 0.2}, {1.0, 1.5} );
    clear( sdl, df, renderer );
    waitEnter();

    h->addPoint( {0.0, 0.0}, {-1.0, -1.0} );
    clear( sdl, df, renderer );
    waitEnter();

    return 0;
}
