/* polygonClipper.h
 * Interface para objetos capazes de fazer aparos em polígonos.
 */
#ifndef POLYGON_CLIPPING_H
#define POLYGON_CLIPPING_H

#include "render/clipping/clippingArea.h"
#include "geometric/polygon.h"

#include <vector>  // std::vector

template <int N>
class PolygonClipper {
public:
    /* Altera a área de clipping para a área passada. */
    virtual void setArea( ClippingArea ) = 0;

    /* Efetua o clipping no polígono passado como parâmetro.
     *
     * Caso o polígono esteja completamente dentro da área
     * de clipping, o valor de retorno será um vetor contendo
     * o próprio polígono recebido como parâmetro.
     *
     * Caso o polígono esteja parcialmente dentro da área de
     * clipping, o valor de retorno será um vetor contendo um
     * ou vários polígonos resultantes da operação de clipping.
     *
     * Caso o polígono esteja completamente fora da área de
     * clipping, o valor de retorno será um vetor vazio. */
    virtual std::vector<Polygon> clip( Polygon& ) = 0;

    virtual ~PolygonClipper() = default;
};

#endif // POLYGON_CLIPPING_H
