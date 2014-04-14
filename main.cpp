/* main.cpp */

// Include *
#include <SDL.h>
#include "view/SDLScreen.h"
#include "view/pixel.h"
#include "view/viewport.h"
#include "window.h"
#include "viewportTransform.h"
#include "screenRenderer.h"
#include "displayFile.h"
#include "geometric/polygon.h"
#include "geometric/drawablePoint.h"
#include "linearOperator.h"
#include "math/constant.h"

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
    SDLScreen sdl( 800, 600, "Teste" );
    sdl.setColor( 255, 255, 255, 255 );
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );

    ViewportTransform vptransform( Viewport::generateViewport( &sdl ),
            {0, 0, 4, 3} );

    ScreenRenderer renderer( vptransform, &sdl );

    DisplayFile df;

    Point<2>* pv1 = new Point<2>[3] {
            {1.0, 1.0}, 
            {1.0, 2.0}, 
            {2.0, 1.0}
            };
    Polygon * p1 = new Polygon( pv1, 3 );

    Point<2>* pv2 = new Point<2>[4] {
            {2.0, 2.0}, 
            {3.0, 2.0}, 
            {3.0, 3.0}, 
            {2.0, 3.0}
            }; 
    Polygon * p2 = new Polygon( pv2, 4 );

    DrawablePoint * p3 = new DrawablePoint( {2, 1.5} );

    df.addObject( p1 );
    df.addObject( p2 );
    df.addObject( p3 );
    df.draw( &renderer );

    sdl.update();
    waitEnter();
    
    LinearOperator<2> scale = make2DScale( 0.75, {2, 1.5} );
    for( int k = 0; k < 2; k++ ) {
        for( int i = 0; i < 3; i++ )
            pv1[i] = scale(pv1[i]);
        for( int i = 0; i < 4; i++ )
            pv2[i] = scale(pv2[i]);

        clear( sdl, df, renderer );
        waitEnter();
    }

    LinearOperator<2> rotate = make2DRotation( -Math::PI/3, {2, 1.5} );
    for( int k = 0; k < 3; k++ ) {
        for( int i = 0; i < 3; i++ )
            pv1[i] = rotate(pv1[i]);
        for( int i = 0; i < 4; i++ )
            pv2[i] = rotate(pv2[i]);

        clear( sdl, df, renderer );
        waitEnter();
    }
    return 0;
}
