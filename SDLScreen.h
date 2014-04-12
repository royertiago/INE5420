/* SDLScreen.h
 * Classe que implementa a interface Desenhavel para o SDL.
 *
 * Não mais do que um objeto desta classe deve ser instanciado
 * no programa que a usa.
 *
 * TODO: achar nome mais bonito.
 */

#ifndef SDL_SCREEN_H
#define SDL_SCREEN_H

#include "drawable.h"

struct SDL_Window;
struct SDL_Renderer;

class SDLScreen : public Drawable {
public:
    /* Instancia a tela com a altura e largura desejados.
     * title é o título da janela criada.
     */
    SDLScreen( int width, int height, const char * title );

    virtual void setColor( int r, int g, int b, int a ) override;
    virtual void pixel( int x, int y ) override;
    virtual int height() const override;
    virtual int width() const override;
    virtual void update() override;

    virtual ~SDLScreen();

private:
    const int _width, _height;
    SDL_Window * window;
    SDL_Renderer * renderer;
};

#endif // TELA_SDL_H
