/* point.h
 * Contém a definição de um ponto.
 * 
 * Coordenadas homogêneas: pontos n-dimensionais são vetores
 * (n+1)-dimensionais cuja última coordenada é sempre 1. 
 *
 * Isto é uma gambiarra para permitir que translações sejam operações
 * lineares: basta usar a última coordenada para recuperar o deslocament.
 * 
 * É responsabilidade do programador garantir que esta 
 * invariante seja mantida.
 */
#ifndef POINT_H
#define POINT_H

#include "math/vector.h"

namespace Math {

    /* Novamente, abusaremos da não-rigidez do typedef para que
     * vetores (n+1)-dimensionais e pontos n-dimensionais sejam
     * intercambiáveis. */
    template <int N>
    using Point = Vector<N + 1>;

}
#endif // POINT_H
