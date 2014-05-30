/* polynomial.h
 * Classe que representa um polinômio generalizado,
 * com um tipo arbitrário como coeficiente.
 *
 * As exigências sobre o tipo passado são:
 *  - operator*(double) implementado
 *  - operator+(Coefficient) implementado
 *  - construtor padrão disponíveis (e devem representar o vetor zero)
 *  - operador de atribuição implementado (para cópia e atribuição)
 *  - operator-(Coefficient) implementado (para PolynomialIterator)
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <utility> //std::decltype
#include <cstddef> //std::size_t

#include "polynomialIterator.h"
namespace Math {

template< typename Coefficient >
class Polynomial {
    std::vector<Coefficient> c; // Coeficientes

public:
    /* Constrói um polinômio com os coeficientes passados.
     * Os coeficientes estão armazenados de forma que o coeficiente
     * de x^i é c[i].
     * O grau do polinômio será o índice do último elemento. */
    Polynomial( std::vector<Coefficient> );

    /* Constrói o polinômio nulo (que retorna apenas Coefficient()). */
    Polynomial() = default;

    /* Acessa o coeficiente diretamente. 
     * Modificar o coeficiente invalida iteradores. */
    Coefficient& operator[]( size_t index );
    const Coefficient& operator[]( size_t index ) const;

    /* Informa o grau deste polinômio.
     * Note que os coeficientes dos termos de maior grau podem
     * ser equivalentes a zero; este comando ignora isto.
     * Ou seja: o valor que o método retorna pode não corresponder
     * ao grau "efetivo" do polinômio, mas nunca é menor do que ele. */
    int degree() const;

    /* Computa o polinômio no ponto especificado. */
    Coefficient operator()( double at ) const;

    /* Computa o polinômio no ponto at e chama operator()
     * do resultado, passando os tipos restantes.
     *
     * É útil para fazer polinômios de polinômios parecerem-se
     * com funções de duas variáveis. */
    template< typename ... Ts >
    auto operator()( double at, Ts ... ts ) const ->
        decltype( std::declval<Coefficient>()( ts... ) );

    /* Constrói um iterador para este polinômio.
     * t é o ponto inicial de iteração,
     * d é o incremento. */
    PolynomialIterator<Coefficient> iterator( double t, double d ) const;

    /* Multiplicação de polinômios.
     * Note que multiplicação por polinômios sobre double sempre faz
     * sentido; é equivalente à multiplicar por um escalar que se
     * altera. */
    Polynomial<Coefficient> operator*( const Polynomial<double>& ) const;
    Polynomial<Coefficient> operator*( const double& ) const;
    Polynomial<Coefficient> operator+( const Polynomial<Coefficient>& ) const;
    Polynomial<Coefficient> operator-( const Polynomial<Coefficient>& ) const;
    Polynomial<Coefficient> operator-() const;
    friend class Polynomial<double>; // Para uso no operator*
};

// Implementação

template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( std::vector<Coefficient> c ) :
    c( c )
{}

// Acesso a elementos
template< typename Coefficient >
Coefficient& Polynomial<Coefficient>::operator[]( size_t index ) {
    return c[index];
}

template< typename Coefficient >
const Coefficient& Polynomial<Coefficient>::operator[]( size_t index ) const {
    return c[index];
}

template< typename Coefficient >
int Polynomial<Coefficient>::degree() const {
    return c.size() - 1;
}

// Operações

template< typename Coefficient >
Coefficient Polynomial<Coefficient>::operator()( double at ) const {
    // Algoritmo de Horner
    Coefficient ret = Coefficient();
    for( int i = degree(); i >= 0; --i ) {
        ret = ret * at + c[i];
    }
    return ret;
}

template< typename Coefficient >
template< typename ... Ts >
auto Polynomial<Coefficient>::operator()( double at, Ts ... ts ) const ->
    decltype( std::declval<Coefficient>()( ts... ) )
{
    return operator()( at )( ts... );
}

template< typename Coefficient >
PolynomialIterator<Coefficient> Polynomial<Coefficient>::iterator(
        double start, double step ) const
{
    return makeIterator( *this, start, step, degree() );
}

// Operadores aritméticos

template< typename Coefficient >
Polynomial<Coefficient> Polynomial<Coefficient>::operator*(
        const Polynomial<double>& rhs ) const 
{
    int degree = this->degree() + rhs.degree();
    std::vector<Coefficient> c( degree + 1 );
    for( int i = 0; i <= this->degree(); ++i )
        for( int j = 0; j <= rhs.degree(); ++j )
            c[i + j] = c[i + j] + this->c[i] * rhs[j];
    return Polynomial<Coefficient>( c );
}

template< typename Coefficient >
Polynomial<Coefficient> Polynomial<Coefficient>::operator*(
        const double& d ) const
{
    std::vector<Coefficient> co( degree() + 1 );
    for( int i = 0; i <= degree(); ++i )
        co[i] = c[i] * d;
    return Polynomial<Coefficient>( co );
}

template< typename Coefficient >
Polynomial<Coefficient> operator*( const double& d, 
        const Polynomial<Coefficient>& p )
{
    return p * d;
}

template< typename Coefficient >
Polynomial<Coefficient> Polynomial<Coefficient>::operator+(
        const Polynomial<Coefficient>& rhs ) const
{
    const Polynomial<Coefficient>& larger = 
        this->degree() >= rhs.degree() ? *this : rhs;
    const Polynomial<Coefficient>& smaller =
        this->degree() >= rhs.degree() ? rhs : *this;

    /* Agora, smaller referencia o polinômio de menor grau
     * e larger referencia o de maior grau. */
    std::vector<Coefficient> c(larger.degree() + 1);
    int i;
    for( i = 0; i <= smaller.degree(); ++i )
        c[i] = smaller[i] + larger[i];
    for( ; i <= larger.degree(); ++i )
        c[i] = larger[i];
    return Polynomial<Coefficient>( c );
}

template< typename Coefficient >
Polynomial<Coefficient> Polynomial<Coefficient>::operator-() const {
    std::vector<Coefficient> co( degree() + 1 );
    for( int i = 0; i <= degree(); ++i )
        co[i] = -c[i];
    return Polynomial<Coefficient>( co );
}

template< typename Coefficient >
Polynomial<Coefficient> Polynomial<Coefficient>::operator-(
        const Polynomial<Coefficient>& rhs ) const
{
    return (*this) + (-rhs);
}

} // namespace Math

#endif // POLYNOMIAL_H
