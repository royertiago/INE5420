/* polygonClipper.h
 * Interface para objetos capazes de fazer aparos em polígonos.
 */
#ifndef POLYGON_CLIPPING_H
#define POLYGON_CLIPPING_H

#include "math/point.h"
#include "render/clipping/clippingArea.h"

template <int N>
class PolygonClipper {
public:
    /* Altera a área de clipping para a área passada. */
    virtual void setArea( ClippingArea ) = 0;

    /* Efetua o clipping do polígono cujos vértices estão 
     * representados em sentido horário no vetor de pontos
     * 'v' de tamanho 'vertexCount'.
     *
     * Caso o polígono esteja dentro (ou parcialmente dentro)
     * da área de clipping, o valor de retorno deve ser true 
     * e os pontos devem ser modificados para que representem 
     * a versão aparada do polígono.
     *
     * Caso o polígono esteja totalmente fora da área de clipping,
     * false deve ser retornado. A implementação é livre para
     * modificar os objetos neste caso. */
    virtual bool clip( Math::Point<N> * v, int vertexCount ) = 0;

    virtual ~PolygonClipper() = default;
};

#endif // POLYGON_CLIPPING_H
