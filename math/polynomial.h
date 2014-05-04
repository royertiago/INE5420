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

#include <utility> //std::swap
#include <cstddef> //std::size_t

namespace Math {

template< typename Coefficient > class Polynomial;

template< typename Coefficient >
class PolynomialIterator {
    const Polynomial< Coefficient > & p;
    Coefficient * delta;
    double t;
    double d;
    int validDeltas;

public:
    PolynomialIterator( const Polynomial<Coefficient> &, double t, double d );
    PolynomialIterator( const PolynomialIterator & );
    ~PolynomialIterator();
    void start( double start );
    void step( double step );
    operator Coefficient() const;
    double current() const;
    void operator++();

};

template< typename Coefficient >
class Polynomial {
    Coefficient * c; // Coeficientes
    int d; // Grau (degree) do polinômio

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

    /* Acessa o coeficiente diretamente. */
    Coefficient& operator[]( size_t index );
    const Coefficient& operator[]( size_t index ) const;

    /* Informa o grau deste polinômio.
     * Note que os coeficientes dos termos de maior grau podem
     * ser equivalentes a zero; este comando ignora isto.
     * Ou seja: o valor que o método retorna pode não corresponder
     * ao grau efetivo do polinômio, mas nunca é menor do que ele. */
    int degree() const;

    /* Computa o polinômio no ponto especificado. */
    Coefficient operator()( double at ) const;

    PolynomialIterator<Coefficient> iterator( double t, double d ) const;
};

// Implementações

// Construtores / Destrutores / Operadores de atribuição
template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( Coefficient * c, int degree ) :
    c( c ),
    d( degree )
{}

template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( const Polynomial<Coefficient>& p ) :
    c( new Coefficient[p.d+1] ),
    d( p.d )
{
    for( int i = 0; i <= d; ++i )
        c[i] = p.c[i];
}

template< typename Coefficient >
Polynomial<Coefficient>::Polynomial( Polynomial<Coefficient>&& p ) :
    c( p.c ),
    d( p.d )
{
    p.c = nullptr;
    p.d = -1;
}

template< typename Coefficient >
Polynomial<Coefficient>& Polynomial<Coefficient>::operator=(
        const Polynomial<Coefficient>& p )
{
    delete[] c;
    c = new Coefficient[p.d+1];
    d = p.d;
    for( int i = 0; i <= d; ++i )
        c[i] = p.c[i];

    return *this;
}

template< typename Coefficient >
Polynomial<Coefficient>& Polynomial<Coefficient>::operator=(
        Polynomial<Coefficient>&& p )
{
    std::swap( c, p.c );
    std::swap( d, p.d );
    return *this;
}

template< typename Coefficient >
Polynomial<Coefficient>::~Polynomial() {
    delete[] c;
}

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
    return d;
}

// Operações

template< typename Coefficient >
Coefficient Polynomial<Coefficient>::operator()( double at ) const {
    // Algoritmo de Horner
    Coefficient ret = Coefficient();
    for( int i = d; i >= 0; --i ) {
        ret = ret * at + c[i];
    }
    return ret;
}

template< typename Coefficient >
PolynomialIterator<Coefficient> Polynomial<Coefficient>::iterator(
        double start, double step ) const
{
    return PolynomialIterator<Coefficient>( *this, start, step );
}

// Iterador
template< typename Coefficient >
PolynomialIterator<Coefficient>::PolynomialIterator(
        const Polynomial<Coefficient>& p, double t, double d ) :
    p( p ),
    delta( new Coefficient[p.degree() + 1] ),
    t( t ),
    d( d ),
    validDeltas( 0 )
{
    delta[0] = p(t);
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::PolynomialIterator(
        const PolynomialIterator<Coefficient> & other ) :
    p( other.p ),
    delta( new Coefficient[other.p.degree() + 1] ),
    t( other.t ),
    d( other.d ),
    validDeltas( other.validDeltas )
{
    for( int i = 0; i <= validDeltas; ++i )
        delta[i] = other.delta[i];
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::~PolynomialIterator() {
    delete delta;
}

template< typename Coefficient >
void PolynomialIterator<Coefficient>::start( double start ) {
    t = start;
    validDeltas = 0;
    delta[0] = p(t);
}

template< typename Coefficient >
void PolynomialIterator<Coefficient>::step( double step ) {
    d = step;
    validDeltas = 0;
}

template< typename Coefficient >
double PolynomialIterator<Coefficient>::current() const {
    return t;
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::operator Coefficient() const {
    return delta[0];
}

template< typename Coefficient >
void PolynomialIterator<Coefficient>::operator++() {
    t += d;
    if( p.degree() + 1 == validDeltas )
        for( int i = validDeltas; i > 0; --i )
            delta[i-1] += delta[i];
    else {
        Coefficient nextDelta = p(t);
        for( int i = 0; i <= validDeltas; ++i ) {
            Coefficient alce = nextDelta;
            nextDelta = nextDelta - delta[i];
            delta[i] = alce;
        }
        ++validDeltas;
    }
}

} // namespace Math

#endif // POLYNOMIAL_H
