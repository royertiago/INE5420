/* polynomialMethods.h
 * Cabeçalho que contém a implementação dos métodos
 * da classe polinômio.
 *
 * Não inclua este header diretamente; inclua o header polynomial.h
 * para ter acesso à toda classe.
 *
 * Os cabeçalhos estão estruturados desta maneira pois a classe
 * Polynomial contém um método que retorna um PolynomialIterator,
 * e esta classe possui, como membro, uma referência para um Polynomial;
 * isto é, temos uma dependência circular.
 *
 * Com classes normais, é possível:
 *  - declarar Polynomial (forward declaration) e definir PolynomialIterator 
 *  num header;
 *  - incluir este header e definir Polynomial num outro;
 *  - pôr as implementações num .cpp.
 * Entretanto, estas estas classes são templatizadas, portanto, a definição 
 * dos métodos devem estar disponíveis no ponto de chamada. Então,
 * polynomial.h inclui este header, para prover as definições necessárias. */
#ifndef POLYNOMIAL_H
#error "Não este header diretamente, inclua polynomial.h em vez disso."
#endif

#ifndef POLYNOMIAL_METHODS_H
#define POLYNOMIAL_METHODS_H

/* Este header só será incluído por polynomial.h, portanto, não precisamos
 * refazer a inclusão. */

namespace Math {

// Construtor
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
PolynomialIterator<Coefficient> Polynomial<Coefficient>::iterator(
        double start, double step ) const
{
    return PolynomialIterator<Coefficient>( *this, start, step );
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

#endif // POLYNOMIAL_METHODS_H
