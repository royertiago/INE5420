/* lineClipper.h
 * Tipos de funções capaz de fazer aparos em linhas.
 *
 * PostLineClipper recorta linhas que já foram projetadas para
 * se encaixarem no quadrado [-1, 1] x [-1, 1], enquanto que
 * PreLineClipper apara linhas antes da projeção, para separar
 * o que fica à frente do plano de projeção e o que fica atrás.
 */
#ifndef LINE_CLIPPING_H
#define LINE_CLIPPING_H

#include "render/projection/projectedPoint.h"
#include "math/vector.h"

/* PreLineClipper<N> é uma função que recebe dois Math::Vector<N>
 * por referência e apara o segmento de reta que une os dois pontos,
 * de forma que a coordenada z dos pontos, após o aparo, seja maior
 * ou igual a 1.
 *
 * O subespaço (N-1)-dimensional determinado por [z == 1] é o plano que
 * contém o plano de projeção; tudo o que ficar atrás deste plano
 * deve ser eliminado.
 *
 * Caso o segmento de reta esteja "à frente" (inteiramente ou parcialmente)
 * de [z == 1], o valor de retorno deve ser true e os pontos
 * devem ser modificados para corresponder à versão aparada deste
 * segmento de reta.
 *
 * Caso o segmento de reta esteja inteiramente "atrás" do plano [z == 1],
 * false deve ser retornado. A implementação é livre para
 * modificar os objetos neste caso. */
template< int N >
using PreLineClipper = bool (*)( Math::Vector<N>&, Math::Vector<N>& );

/* PostLineClipper é uma função que recebe dois ProjectedPoint por referência
 * e efetua o clipping do segmento de reta cujas extremidades 
 * são estes dois pontos.
 *
 * Caso o segmento esteja dentro (ou parcialmente dentro)
 * da área [-1, 1] x [-1, 1] (a área contra o qual os pontos
 * serão aparados), o valor de retorno deve ser true 
 * e os pontos devem ser modificados para que representem 
 * a versão aparada do segmento de reta.
 *
 * Caso o segmento esteja totalmente fora da área de clipping,
 * false deve ser retornado. A implementação é livre para
 * modificar os objetos neste caso. */
typedef bool (* PostLineClipper)( ProjectedPoint&, ProjectedPoint& );

#endif // LINE_CLIPPING_H
