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
#include "windowTransform.h"
#include "clippingArea.h"
#include "test/lib/testList.h"

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
    if( Test::run() == false ) {
        return 1;
    }

    SDLScreen sdl( 600, 600, "Teste" );
    sdl.setColor( 255, 255, 255, 255 );
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );


    WindowTransform wt( ClippingArea::normalized );
    Viewport v = Viewport::generateViewport( &sdl );
    ScreenRenderer renderer( v, wt, sdl );

    DisplayFile df;

    Polygon * p1 = new Polygon( new Point<2>[3]{
            {.25, .25}, 
            {0.25, 0.5}, 
            {0.5, 0.25}
            }, 3 );

    Polygon * p2 = new Polygon( new Point<2>[4]{
            {0.5, 0.5}, 
            {0.75, 0.5}, 
            {0.75, 0.75}, 
            {0.5, 0.75}
            }, 4); 

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

    //TesteDeUnidadeDix:
    Math::Vector<2> vec{1.0, 2.0};
    printf( "%lf %lf\n", vec[0][0], vec[1][0] ); //1.0 2.0
    vec[0] = vec[1] = 3.0;
    printf( "%lf %lf\n", vec[0][0], vec[1][0] ); //3.0 3.0
    vec[0] = 1 + (vec[1] = 2.5);
    printf( "%lf %lf\n", vec[0][0], vec[1][0] ); //3.5 2.5

    return 0;
}
