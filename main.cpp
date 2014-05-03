/* main.cpp */

// Include *
#include <SDL.h>
#include "displayFile.h"
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

/*    SDLScreen sdl( 600, 600, "Teste" );
    sdl.setColor( 255, 255, 255, 255 );
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );


    WindowTransform wt( ClippingArea::normalized );
    Viewport v = Viewport::generateViewport( &sdl );
    v.xmin += 10;
    v.ymin += 10;
    v.xmax -= 10;
    v.ymax -= 10;
    CohenSutherland NLN( ClippingArea::normalized );
    ScreenRenderer renderer( v, wt, NLN, sdl );

    DisplayFile df;

    Polygon * p1 = GeometricFactory::makePolygon(
            {.25, .25}, {0.25, 0.5}, {0.5, 0.25} );

    Polygon * p2 = GeometricFactory::makePolygon(
            {0.5, 0.5}, {0.75, 0.5}, {0.75, 0.75}, {0.5, 0.75} ); 

    DrawablePoint * p3 = new DrawablePoint( {0.4, 0.4} );

    df.addObject( p1 );
    df.addObject( p2 );
    df.addObject( p3 );
    df.draw( &renderer );

    sdl.update();
    waitEnter();
    
    for( int i = 0; i < 6; i++ ) {
        wt.window().rotate( Math::PI/12 );
        clear( sdl, df, renderer );
        waitEnter();
    }

    for( int i = 0; i < 3; i++ ) {
        wt.window().moveUp({ 0, 0.15 });
        clear( sdl, df, renderer );
        waitEnter();
    }

    for( int i = 0; i < 3; i++ ) {
        wt.window().hscale( 1.15 );
        clear( sdl, df, renderer );
        waitEnter();
    }
*/
    return 0;
}
