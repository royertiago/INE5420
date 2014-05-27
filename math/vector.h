/* vector.h
 * Contém a definição de um vetor e algumas funções para trabalhar
 * com eles.
 *
 * Tome cuidado para não confundir Math::Vector com std::vector.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "matrix.h"

namespace Math {

    /* Aqui, o fato de typedef ser não-estrito é uma propriedade bastante
     * útil: a função de multiplicação, por exemplo, toma uma matriz MxN
     * e outra NxP e devolve uma MxP. Caso P seja 1, o valor retornado
     * será uma matriz Mx1 - o que, de acordo com a seguinte definição,
     * é um vetor: */
    template< int M, typename T = double >
    using Vector = Matrix< M, 1, T >;

    /* Computa o produto interno entre os dois vetores passados. */
    template< int M >
    double innerProduct( Vector<M>, Vector<M> );

    /* Retorna o ângulo entre os dois vetores, em radianos.
     * Assumiremos que os dois vetores são não-nulos. */
    template< int M >
    double vectorAngle( Vector<M>, Vector<M> );

    /* Computa a norma do vetor. */
    template< int M >
    double norm( Vector<M> );

    /* Retorna o produto cruzado u x v.
     * O produto cruzado é ortogonal simultaneamente a u e v. */
    Vector<3> crossProduct( Vector<3> u, Vector<3> v );

// Implementação
template< int M >
double innerProduct( Vector<M> u, Vector<M> v ) {
    double p = 0;
    for( int i = 0; i < M; ++i )
        // fma( x, y, z ) == x*y + z
        p = std::fma( u[i], v[i], p );
    return p;
}

template< int M >
double vectorAngle( Vector<M> u, Vector<M> v ) {
    return std::acos( innerProduct(u, v) / (norm(v) * norm(u)) );
}

template< int M >
double norm( Vector<M> v ) {
    return std::sqrt( innerProduct(v, v) );
}

} // namespace Math

#endif // VECTOR_H
