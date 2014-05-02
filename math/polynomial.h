/* polynomial.h
 * Classe que representa um polinômio generalizado,
 * com um tipo arbitrário como coeficiente.
 *
 * As exigências sobre o tipo passado são:
 *  - operator*(double) implementado
 *  - operator+(Coefficient) implementado
 *  - construtor padrão disponíveis (e devem representar o vetor zero)
 *  - operador de atribuição implementado (para cópia e atribuição)
 */
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <utility>

namespace Math {

template< typename Coefficient >
class Polynomial {
    Coefficient * c; // Coeficientes
    int degree;

public:
    /* Constrói um polinômio com os coeficientes passados.
     * Os coeficientes estão armazenados de forma que o coeficiente
     * de x^i é c[i].
     * degree é o último coeficiente calculado; note que o tamanho
     * do vetor deve ser degree + 1.
     *
     * Este objeto assumirá controle sobre o vetor passado. */
    Polynomial( Coefficient * c, int degree );

    Polynomial( const Polynomial<Coefficient>& );
    Polynomial( Polynomial<Coefficient>&& );
    Polynomial<Coefficient>& operator=( const Polynomial<Coefficient>& );
    Polynomial<Coefficient>& operator=( Polynomial<Coefficient>&& );
    ~Polynomial();

    /* Computa o polinômio no ponto especificado. */
    Coefficient operator()( double at ) const;
};

// Implementações

// Construtores / Destrutores / Operadores de atribuição
template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( Coefficient * c, int degree ) :
    c( c ),
    degree( degree )
{}

template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( const Polynomial<Coefficient>& p ) :
    c( new Coefficient[p.degree] ),
    degree( p.degree )
{
    for( int i = 0; i < degree; ++i )
        c[i] = p.c[i];
}

template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( Polynomial<Coefficient>&& p ) :
    c( p.c ),
    degree( p.degree )
{
    p.c = nullptr;
    p.degree = -1;
}

template< typename Coefficient >
Polynomial<Coefficient>& Polynomial<Coefficient>::operator=(
        const Polynomial<Coefficient>& p )
{
    delete[] c;
    c = new Coefficient[p.degree];
    degree = p.degree;
    for( int i = 0; i < degree; ++i )
        c[i] = p.c[i];

    return *this;
}

template< typename Coefficient >
Polynomial<Coefficient>& Polynomial<Coefficient>::operator=(
        Polynomial<Coefficient>&& p )
{
    std::swap( c, p.c );
    std::swap( degree, p.degree );
    return *this;
}

template< typename Coefficient >
Polynomial<Coefficient>::~Polynomial() {
    delete[] c;
}

// Operador de chamada de funcão

template< typename Coefficient >
Coefficient Polynomial<Coefficient>::operator()( double at ) const {
    // Algoritmo de Horner
    Coefficient ret;
    for( int i = degree; i >= 0; --i )
        ret = ret * at + c[i];
    return ret;
}

} // namespace Math

#endif // POLYNOMIAL_H
