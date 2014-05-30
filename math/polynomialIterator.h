/* polynomialIterator.h
 * Classe que implementa o algoritmo forward differences, para calcular
 * o valor de um polinômio em múltiplos pontos espaçados uniformemente
 * num intervalo.
 *
 * Funcionamento do iterador:
 *
 * Fixado h, defina Df(t) = f(t + h) - f(t).
 * Então, f(t + h) = f(t) + Df(t).
 * Repetindo com Df: DDf(t) = D^2f(t) = Df(t + h) - Df(t), ou seja,
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
 *
 * Entretanto, a perda de precisão pode ser significativa; neste caso,
 * para reinicializar o iterador, utilize o método start cujo parâmetro
 * é o próprio iterador (start recebe um double e operator double() retorna
 * o ponto atual da iteração).
 *
 * Note que iterador é um template: ele aceita qualquer classe que possua
 * operator(double) implementado. Entetanto, o algoritmo funciona corretamente
 * apenas com polinômios.
 *
 * Devido à necessidade de informar o tipo exato do polinômio e do coeficiente
 * na construção, existe uma função MakeIterator, que retorna um iterador.
 * Como esta função está diretamente no namespace Math, o compilador
 * é capaz de deduzir os parâmetros do template.
 */
#ifndef POLYNOMIAL_ITERATOR_H
#define POLYNOMIAL_ITERATOR_H

#include <vector>
#include <utility>

namespace Math {

template< typename Coefficient >
class PolynomialIterator {
    // delta[i] guarda o valor de D^if(t). delta[0] = f(t).
    mutable std::vector<Coefficient> delta;

    double t; // atual ponto em que está sendo calculado o vetor.
    double h; // variação do iterador.
    int d; // grau do polinômio

public:
    /* Constrói um iterador para o polinômio passado.
     * t é o ponto inicial da iteração,
     * h é o incremento,
     * d é o grau do polinômio. */
    template< typename Polynomial >
    PolynomialIterator( const Polynomial&, double t, double h, int d );

    /* Informa qual é o ponto atual da iteração. */
    operator double() const;

    /* Retorna o valor atual do polinômio. */
    Coefficient operator*() const;

    /* Avança o iterador. */
    void operator++();
};

/* Retorna um iterador para o polinômio p.
 * t é o ponto inicial da iteração,
 * h é o incremento,
 * d é o grau do polinômio. */
template< typename Polynomial, typename Coefficient = 
    decltype( std::declval<Polynomial>()(0.0) ) >
PolynomialIterator<Coefficient> makeIterator( const Polynomial& p,
        double t, double h, int d )
{
    return PolynomialIterator<Coefficient>( p, t, h, d );
}

// Implementação

template< typename Coefficient >
template< typename Polynomial >
PolynomialIterator<Coefficient>::PolynomialIterator(
        const Polynomial& p, double t, double h, int d ) :
    delta( d + 1 ),
    /* Precisamos de d posições para cada um dos deltas, mais
     * uma para o valor do próprio polinômio. */
    t( t ),
    h( h ),
    d( d )
{
    t = t - d*h;
    // Lembre-se de que estamos mexendo no argumento, não em this->t

    for( int validDeltas = 0; validDeltas <= d; ++validDeltas ) {
        // Existem mais deltas a serem atualizados.
        Coefficient nextDelta = p(t);
        for( int i = 0; i <= validDeltas; ++i ) {
            /* delta[i] será modificado para nextDelta, mas antes precisamos
             * computar qual é o próximo valor de nextDelta. */
            Coefficient alce = nextDelta;
            nextDelta = nextDelta - delta[i];
            delta[i] = alce;
        }
        /* Note que a posição delta[validDeltas] já foi atualizada para
         * o valor antigo de nextDelta. Lemos lixo para nextDelta antes,
         * mas não tem problema, pois nunca mexemos com nextDelta de novo. */
        t += h;
    }
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::operator double() const {
    return t;
}

template< typename Coefficient >
Coefficient PolynomialIterator<Coefficient>::operator*() const {
    return delta[0];
}

template< typename Coefficient >
void PolynomialIterator<Coefficient>::operator++() {
    t += h;
    for( int i = d; i > 0; --i )
        delta[i-1] = delta[i-1] + delta[i];
}

} // namespace Math

#endif // POLYNOMIAL_ITERATOR_H
