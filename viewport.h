/* viewport.h
 * Tipo POD que delimita uma área de desenho "física".
 */

class Drawable;

struct Viewport {
    int xmin;
    int xmax;
    int ymin;
    int ymax;

    /* Constrói uma viewport a partir do desenhável passado,
     * que engloba todos os pixels desenháveis do desenhável.
     */
    static Viewport generateViewport( Drawable* );
};
