/* lineClipper.h
 * Tipo de função capaz de fazer aparos em linhas.
 */
#ifndef LINE_CLIPPING_H
#define LINE_CLIPPING_H

#include "render/projection/projectedPoint.h"

/* LineClipper é uma função que recebe dois ProjectedPoint por referência
 * e efetua o clipping do segmento de reta cujas extremidades 
 * são estes dois pontos.
 *
 * Caso o segmento esteja dentro (ou parcialmente dentro)
 * da área de clipping, o valor de retorno deve ser true 
 * e os pontos devem ser modificados para que representem 
 * a versão aparada do segmento de reta.
 *
 * Caso o segmento esteja totalmente fora da área de clipping,
 * false deve ser retornado. A implementação é livre para
 * modificar os objetos neste caso. */
typedef bool (* LineClipper)( ProjectedPoint&, ProjectedPoint& );

#endif // LINE_CLIPPING_H
