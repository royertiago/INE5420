/* main.cpp */

// Include *
#include <SDL.h>
#include "displayFile.h"
#include "geometric/cubicSpline.h"
#include "geometric/drawablePoint.h"
#include "geometric/geometricFactory.h"
#include "geometric/polygon.h"
#include "math/constant.h"
#include "math/linearOperator.h"
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

    CubicSpline<2> * s1 = new CubicSpline<2>(
            new Vector<2>[4]{{      0,        0},
                             {1.0/3.0, -1.0/3.0},
                             {      0,        0},
                             {      0,        1}},
            {0.5, 0.5} );

    CubicSpline<2> * s2 = new CubicSpline<2>(
            new Vector<2>[4]{{      0,        0},
                             {    1.0,      1.0},
                             {      0,        0},
                             {      0,       -1}},
            {0.5, 0.5} );

    CubicSpline<2> * s3 = new CubicSpline<2>(
            new Vector<2>[4]{{      0,        0},
                             {    1.0,      1.0},
                             {      0,        0},
                             {   -0.5,        0}},
            {0.5, 0.5} );

    df.addObject( s1 );
    df.addObject( s2 );
    df.addObject( s3 );

    clear( sdl, df, renderer );
    waitEnter();
    
    return 0;
}
