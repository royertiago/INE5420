/* Implementação de SDLScreen.h */

#include <SDL.h>
#include <stdexcept>
#include <string>
using std::string;
using std::runtime_error;

#include "SDLScreen.h"

SDLScreen::SDLScreen( int width, int height, const char * title ) :
    _width( width ),
    _height( height )
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        throw runtime_error( string("SDL_Init(): ") + SDL_GetError() );

    window = SDL_CreateWindow( title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN
            );

    if( window == nullptr ) {
        throw runtime_error( string("SDL_CreateWindow(): ")
                + SDL_GetError() );
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == nullptr ) {
        throw runtime_error( string("SDL_CreateRenderer(): ")
                + SDL_GetError() );
    }

}

void SDLScreen::setColor( int r, int g, int b, int a ) {
    SDL_SetRenderDrawColor( renderer, uint8_t(r), uint8_t(g),
            uint8_t(b), uint8_t(a) );
}

void SDLScreen::paint( Pixel p ) {
    SDL_RenderDrawPoint( renderer, p.x, p.y );
}

void SDLScreen::paint( Pixel a, Pixel b ) {
    SDL_RenderDrawLine( renderer, a.x, a.y, b.x, b.y );
}

int SDLScreen::height() const {
    return _height;
}

int SDLScreen::width() const {
    return _width;
}

void SDLScreen::update() {
    SDL_RenderPresent( renderer );
}

SDLScreen::~SDLScreen() {
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}
