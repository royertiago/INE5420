/* viewportTransform.h
 * Classe responsável por fazer a transformada de viewport.
 */

#include "pixel.h"

class ViewportTransform {
public:
    /* Cria um transformador de viewport com a viewport e window
     * especificadas. */
    ViewportTransform( Viewport viewport, Window window );

    Pixel transform( Point<2> );
private:
