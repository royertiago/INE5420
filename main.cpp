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

void waitEnter() {
    SDL_Event e;
    while( true )
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                if( e.key.keysym.sym == SDLK_RETURN )
                    goto melga;

melga: return;
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

    Polygon * p1 = new Polygon( new Point<2>[3] {
            Point<2>({1.0, 1.0}), Point<2>({1.0, 2.0}), Point<2>({2.0, 1.0})
            }, 3);
    Polygon * p2 = new Polygon( new Point<2>[4] {
            Point<2>({2.0, 2.0}), Point<2>({3.0, 2.0}), Point<2>({3.0, 3.0}), Point<2> ({2.0, 3.0}) //TODO: sintaxe horrível
            }, 4);

    DrawablePoint * p3 = new DrawablePoint( Point<2>({2.5, 2.5}) );

    df.addObject( p1 );
    df.addObject( p2 );
    df.addObject( p3 );
    df.draw( &renderer );

    sdl.update();
    waitEnter();
    
    renderer.viewportTransform().window().hscale( 2.0 );
    sdl.setColor( 255, 255, 255, 255 ); //clear - devemos pôr isto num método
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );
    df.draw( &renderer );
    sdl.update();
    waitEnter();

    renderer.viewportTransform().window().vscale( 2.0 );
    sdl.setColor( 255, 255, 255, 255 ); //clear - devemos pôr isto num método
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );
    df.draw( &renderer );
    sdl.update();
    waitEnter();

    renderer.viewportTransform().window().move( -0.5, -0.5 );
    sdl.setColor( 255, 255, 255, 255 ); //clear - devemos pôr isto num método
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );
    df.draw( &renderer );
    sdl.update();
    waitEnter();

    renderer.viewportTransform().window().move( -0.5, -0.5 );
    sdl.setColor( 255, 255, 255, 255 ); //clear - devemos pôr isto num método
    for( int i = 0; i < sdl.width(); i++ )
        for( int j = 0; j < sdl.height(); j++ )
            sdl.paint({ i, j });
    sdl.setColor( 0, 0, 0, 255 );
    df.draw( &renderer );
    sdl.update();
    waitEnter();
    //GAMBIRARRA:
    /*bool quit = false;
    while( !quit ) {
        SDL_Event e;
        while( SDL_PollEvent(&e) != 0 )
            if( e.type == SDL_QUIT )
                quit = true;
        SDL_Delay( 20 ); //Não torrar o processador
    } //TODO: descobrir uma forma de tirar este tipo de código do main. */

    return 0;
}
