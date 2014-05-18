/* viewport.h
 * Tipo POD que delimita uma área de desenho "física".
 * 
 * As extremidades da viewport (xmin/ymin/xmax/ymax) estão em coordenadas
 * da viewport e representam valores em pixels.
 *
 * A viewport traduz coordenadas de window projetada para coordenadas
 * de viewport, mapeando ProjectedPoint para Pixel. As coordenadas de
 * ProjectedPoint estão de acordo com a matemática usual, enquanto que
 * em Pixel está invertido: aumentando y, o ponto "desce". Esta classe
 * faz a inversão corretamente.
 */
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "view/pixel.h"
#include "projection/projectedPoint.h"
class Drawable;

struct Viewport {
    int xmin;
    int ymin;
    int xmax;
    int ymax;

    /* Constrói uma viewport a partir do desenhável passado,
     * que engloba todos os pixels visíveis do desenhável.
     */
    static Viewport generateViewport( Drawable* );

    /* Quantidade de pixels na viewport. */
    int area() const;

    /* Transforma o ponto passado de coordenadas de window projetadas
     * para coordenadas de viewport.
     *
     * O ponto passado deve estar no quadrado [-1, 1] x [-1, 1]. */
    Pixel transform( ProjectedPoint ) const;
};

#endif // VIEWPORT_H
