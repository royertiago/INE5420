/* clippingArea.h
 * Tipo POD que representará a área de clipping, dentro das coordenadas
 * da window.
 *
 * Existem três sistemas de coordenadas: mundo, window e viewport.
 * O objeto window está em coordenadas do mundo, e é capaz de mapear
 * pontos de seu interior para o interior desta área de clipping de
 * forma proporcional (e o mesmo para pontos no exterior da window).
 * No sistema de coordenadas da window, que é paralelo ao sistema
 * de coordenadas da viewport, é que rodam os algoritmos de clipping.
 * Este objeto delimita a área de clipping.
 */
#ifndef CLIPPING_AREA_H
#define CLIPPING_AREA_H

#include "math/vector.h"

struct ClippingArea {
    double xmin;
    double ymin;
    double xmax;
    double ymax;

    /* Movimenta a área de clipping no sentido desejado. */
    void move( double x, double y );
    void move( Math::Vector<2> v );

    /* vertical scale: Multiplica a altura da window pelo fator
     * desejado sem alterar seu centro. */
    void vscale( double factor );

    /* horizontal scale: Multiplica a largura da window pelo
     * fator desejado sem alterar seu centro. */
    void hscale( double factor );

    static const ClippingArea normalized;
};

#endif // CLIPPING_AREA_H
