/* interpolation.h
 * Define que geram polinômios que interpolam de pontos e polinômios.
 */
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "math/polynomial.h"

namespace Interpolation {
    using Math::Polynomial;

    /* Estes dois polinômios são usados em funções de interpolação.
     * Para interpolar os pontos u e v a fórmula é
     * p(t) = (1-t) u + t * v
     *      = oneMinusT * u + identity * v; */
    const static Polynomial<double> identity( std::vector<double>{0, 1} );
    const static Polynomial<double> oneMinusT( std::vector<double>{1, -1} );

    /* Constrói um polinômio que irá interpolar os pontos u e v. */
    template< typename Coefficient >
    Polynomial<Coefficient> linear( Coefficient u, Coefficient v );

    /* Constrói um polinômio que irá interpolar, linearmente, os polinômios
     * u e v; isto é, p(t) = (1-t) u(t) + t * v(t) */
    template< typename Coefficient >
    Polynomial<Coefficient> linear(
            Polynomial<Coefficient> u,
            Polynomial<Coefficient> v );

// Implementações

template< typename Coefficient >
Polynomial<Coefficient> linear( Coefficient u, Coefficient v ) {
    return Polynomial<Coefficient>( std::vector<Coefficient>{u, v-u} );
}

template< typename Coefficient >
Polynomial<Coefficient> linear( 
        Polynomial<Coefficient> u,
        Polynomial<Coefficient> v )
{
    return u * oneMinusT + v * identity;
}

} // namespace Interpolation

#endif // INTERPOLATION_H
