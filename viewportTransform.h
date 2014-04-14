/* viewportTransform.h
 * Classe responsável por fazer a transformada de viewport.
 */
#ifndef VIEWPORT_TRANSFORM_H
#define VIEWPORT_TRANSFORM_H

#include "view/pixel.h"
#include "point.h"
#include "view/viewport.h"
#include "window.h"

class ViewportTransform {
    Viewport _viewport;
    Window _window;

public:
    /* Cria um transformador de viewport com a viewport e window
     * especificadas. */
    ViewportTransform( Viewport viewport, Window window );

    /* Computa a transformada de viewport para o dado ponto. */
    Pixel transform( Point<2> ) const;

    /* Computa as coordenadas de mundo para o dado pixel. */
    Point<2> transform( Pixel ) const;

    /* Retorna uma referência para a viewport deste objeto. */
    Viewport& viewport() { return _viewport; }
    const Viewport& viewport() const { return _viewport; }

    /* Retorna uma referência para a window deste objeto. */
    Window& window() { return _window; }
    const Window& window() const { return _window; }

    /* Retorna a densidade. TODO: documentar */
    double density() const;
};

#endif // VIEWPORT_TRANSFORM_H
