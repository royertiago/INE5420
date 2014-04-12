/* viewport.h
 * Tipo POD que delimita uma área de desenho "física".
 */
#ifndef VIEWPORT_H
#define VIEWPORT_H

class Drawable;

struct Viewport {
    int xmin;
    int ymin;
    int xmax;
    int ymax;

    /* Constrói uma viewport a partir do desenhável passado,
     * que engloba todos os pixels desenháveis do desenhável.
     */
    static Viewport generateViewport( Drawable* );
};

#endif // VIEWPORT_H
