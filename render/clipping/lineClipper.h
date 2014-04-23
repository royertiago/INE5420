/* lineClipper.h
 * Interface para objetos capazes de fazer aparos em linhas.
 */
#ifndef LINE_CLIPPING_H
#define LINE_CLIPPING_H

#include "math/point.h"
#include "render/clipping/clippingArea.h"

template <int N>
class LineClipper {
public:
    /* Altera a área de clipping para a área passada. */
    virtual void setArea( ClippingArea ) = 0;

    /* Efetua o clipping do segmento de reta cujas extremidades 
     * estão nos pontos passados.
     *
     * Caso o segmento esteja dentro (ou parcialmente dentro)
     * da área de clipping, o valor de retorno deve ser true 
     * e os pontos devem ser modificados para que representem 
     * a versão aparada do segmento de reta.
     *
     * Caso o segmento esteja totalmente fora da área de clipping,
     * false deve ser retornado. A implementação é livre para
     * modificar os objetos neste caso. */
    virtual bool clip( Math::Point<N>&, Math::Point<N>& ) = 0;

    virtual ~LineClipper() = default;
};

#endif // LINE_CLIPPING_H
