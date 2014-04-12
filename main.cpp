#include <SDL.h>
#include "view/SDLScreen.h"
#include "pixel.h"

int main() {
    SDLScreen t( 800, 600, "Teste" );

    t.setColor( 255, 255, 255, 255 );
    for( int i = 0; i < t.width(); i++ )
        for( int j = 0; j < t.height(); j++ )
            t.paint( {i, j} ); //Pinta a tela de branco

    t.setColor( 255, 0, 255, 255 );
    for( int i = 0; i < 100; i++ )
        for( int j = i; j < 100; j++ )
            t.paint( {100 + i, 100 + j} );

    t.setColor( 255, 255, 0, 255 );
    for( int i = 0; i <= 20; i++ )
        t.paint( {300, 200 + 10*i}, {400, 300} );

    t.update();

    //GAMBIRARRA:
    bool quit = false;
    while( !quit ) {
        SDL_Event e;
        while( SDL_PollEvent(&e) != 0 )
            if( e.type == SDL_QUIT )
                quit = true;
        SDL_Delay( 20 ); //Não torrar o processador
    } //TODO: descobrir uma forma de tirar este tipo de código do main.

    return 0;
}
