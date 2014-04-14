/* vector.h
 * Contém a definição de um vetor.
 *
 * Não é uma definição elaborada - é um template alias - mas
 * merece seu próprio header pela quantidade de usos independente
 * da classe Matrix.
 *
 * Tome cuidado para não confundir Math::Vector com std::vector.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

namespace Math {

    /* Aqui, o fato de typedef ser não-estrito é uma propriedade bastante
     * útil: a função de multiplicação, por exemplo, toma uma matriz MxN
     * e outra NxP e devolve uma MxP. Caso P seja 1, o valor retornado
     * será uma matriz Mx1 - o que, de acordo com a seguinte definição,
     * é um vetor: */
    template <int M>
    using Vector = Matrix<M, 1>;

}

#endif // VECTOR_H
