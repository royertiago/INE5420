/* polynomialIterator.h
 * Classe que implementa o algoritmo forward differences, para calcular
 * o valor de um polinômio em múltiplos pontos espaçados uniformemente
 * num intervalo.
 *
 * Fixado h, defina Df(t) = f(t + h) - f(t).
 * Então, f(t + h) = f(t) + Df(t).
 * Por outro lado, DDf(t) = D^2f(t) = Df(t + h) - Df(t), ou seja,
 * Df(t + h) = Df(t) + D^2f(t + h).
 * Para um polinômio de grau n, é possível mostrar que D^nf(t) é
 * constante; portanto, podemos calcular f(t + k*h) para vários valores
 * de k fazendo apenas somas.
 *
 * Para um polinômio quadrático, por exemplo, precisamos do valor
 * de f em três pontos distintos para que possamos calcular Df e DDf para
 * o primeiro ponto; a partir daí, sabemos que DDf será sempre constante,
 * então podemos, ao invés de usar os valores do polinômio para calcular
 * os deltas, usar os valores dos deltas para calcular os próximos valores
 * do polinômio.
 */
#ifndef POLYNOMIAL_ITERATOR_H
#define POLYNOMIAL_ITERATOR_H

namespace Math {

template< typename Coefficient > class Polynomial;

template< typename Coefficient >
class PolynomialIterator {
    const Polynomial< Coefficient > & p;
    // delta[i] guarda o valor de D^if(t). delta[0] = f(t).
    Coefficient * delta;

    // t é o atual ponto em que está sendo calculado o vetor.
    double t;

    // h é a variação do iterador.
    double h;

    /* Inicialmente, a única posição valida é a inicial (delta[0]).
     * Conforme operator++() vai sendo executado, podemos computar as
     * variações, e as variações das variações, e assim por diante,
     * até atingirmos o nível p.degree(), em que as variações das
     * variações tornam-se constantes.
     * Esta variável registra quantos níveis de variações já calculamos. */
    int validDeltas;

public:
    /* Constrói um iterador para o polinômio passado.
     * t é o ponto inicial da iteração,
     * h é o incremento. */
    PolynomialIterator( const Polynomial<Coefficient> &, double t, double h );

    PolynomialIterator( const PolynomialIterator & );

    // Utilizar o iterador que sofreu o std::move causará erro de segmento. 
    PolynomialIterator( PolynomialIterator&& );

    ~PolynomialIterator(); // Precisamos gerenciar o ponteiro delta.


    /* Altera o ponto inicial da iteração.
     * Esta operação reseta o iterador; para calcular o próximo ponto,
     * utilize operator++(). */
    void start( double start );

    /* Altera o valor do incremento.
     * Esta operação reseta o iterador. */
    void step( double step );

    /* Informa qual é o ponto atual da iteração. */
    double current() const;

    /* Retorna o valor atual do polinômio. */
    operator Coefficient() const;

    /* Avança o iterador. */
    void operator++();
};

} // namespace Math

#include "polynomialIteratorMethods.h"

#endif // POLYNOMIAL_ITERATOR_H
