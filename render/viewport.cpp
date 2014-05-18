/* viewport.cpp
 * Implementação de viewport.h
 */

#include "render/viewport.h"

#include "view/drawable.h"

Viewport Viewport::generateViewport( Drawable * d ) {
    return Viewport{ 0, 0, d->width(), d->height() };
}

int Viewport::area() const {
    return (xmax - xmin) * (ymax - ymin);
}

Pixel Viewport::transform( ProjectedPoint p ) const {
    /* p veio do quadrado [-1, 1] x [-1, 1] e deve ser mapeado
     * para o retângulo [xmin, xmax] x [ymin, ymax]. */

    Pixel r; // Valor de retorno

    /* xratio representa a proporção entre o a coordenada x de p
     * e o lado do quadrado em que ele está contido. */
    double xratio = (p.x + 1)/2;
    r.x = xmin + xratio * (xmax - xmin);

    /* O uso de yratio deveria ser o mesmo de xratio, entretanto, precisamos
     * inverter a coordenada y. */
    double yratio = (1 - p.y)/2;
    r.y = ymin + yratio * (ymax - ymin);
    /* Note que definir
     *  double xratio = (p.x + 1)/2;
     *  r.y = ymin + (1 - yratio) * (ymax - ymin);
     * é equivalente. */

    return r;
}
