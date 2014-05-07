/* polynomialIteratorMethods.h
 * Cabeçalho que contém a implementação dos métodos de PolynomialIterator.
 *
 * Não inclua este header diretamente; inclua o cabeçalho polynomialIterator.h
 * para ter acesso à toda classe.
 *
 * Uma explicação deste layout de cabeçalhos pode ser encontrada em
 * polynomialMethods.h */
#ifndef POLYNOMIAL_ITERATOR_H
#error "Não inclua este header diretamente, inclua polynomialIterator.h" \
       " em vez disso."
#endif

#ifndef POLYNOMIAL_ITERATOR_METHODS_H
#define POLYNOMIAL_ITERATOR_METHODS_H

/* Este header só será incluído por polynomialIterator.h, portanto,
 * não precisamos refazer a inclusão. */

#include "polynomial.h"
/* Esta inclusão é segura (e necessária).
 * Existem duas formas de um usuário incluir algum destes cabeçalhos:
 * 1. Incluir primeiro polynomial.h
 * 2. Incluir primeiro polynomialIterator.h
 * (Inclusões múltiplas são protegidas pelos include guards.)
 *
 * Importante notar que polynomial.h inclui polynomialIterator.h antes
 * mesmo de definir POLYNOMIAL_H.
 *
 * Forma 1 segue a seguinte sequência de passos:
 *  polynomial.h inclui polynomialIterator.h
 *   polynomialIterator.h define POLINOMIAL_ITERATOR_H
 *1) polynomialIterator.h define a classe PolynomialIterator
 *   polynomialIterator.h inclui polynomialIteratorMethods.h
 *    polynomialIteratorMethods.h define POLYNOMIAL_ITERATOR_METHODS_H
 *    polynomialIteratorMethods.h inclui polynomial.h
 *     polynomial.h inclui polynomialIterator.h
 *      polynomialIterator.h percebe que POLYNOMIAL_ITERATOR_H está definido
 *      e "retorna".
 *     polynomial.h define POLYNOMIAL_H
 *2)   polynomial.h define a classe Polynomial
 *     polynomial.h inclui polynomialMethods.h
 *      polynomialMethods.h define POLYNOMIAL_METHODS_H
 *3)    polynomialMethods.h define os métodos de Polynomial
 *      polynomialMethods.h "retorna"
 *     polynomial.h "retorna"
 *4)  polynomialIteratorMethods.h define os métododos de PolynomialIterator
 *    polynomialIteratorMethods.h "retorna"
 *   polynomialIterator "retorna"
 *  polynomial.h percebe que POLYNOMIAL_H está definido e "retorna"
 *
 * Note que a definição de Polynomial (2) ocorre depois de PolynomialIterator
 * (1), e a definição dos métodos das classes só ocorre após ambas as
 * classes já terem sido definidas.
 *
 * A forma 2 segue a mesma sequência de passos, exceto por não fazer
 * o primeiro e o último.
 */

namespace Math {

// Construtores / destrutor

template< typename Coefficient >
PolynomialIterator<Coefficient>::PolynomialIterator(
        const Polynomial<Coefficient>& p, double t, double h ) :
    p( p ),
    delta( new Coefficient[p.degree() + 1] ),
    /* Precisamos de p.degree() posições para cada um dos deltas, mais
     * uma para o valor do próprio polinômio. */
    t( t ),
    h( h ),
    validDeltas( 0 )
{}

template< typename Coefficient >
PolynomialIterator<Coefficient>::PolynomialIterator(
        const PolynomialIterator<Coefficient> & other ) :
    p( other.p ),
    delta( new Coefficient[other.p.degree() + 1] ),
    t( other.t ),
    h( other.h ),
    validDeltas( other.validDeltas )
{
    for( int i = 0; i < validDeltas; ++i )
        delta[i] = other.delta[i];
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::PolynomialIterator(
        PolynomialIterator<Coefficient> && other ) :
    p( other.p ),
    delta( other.delta ),
    t( other.t ),
    h( other.h ),
    validDeltas( other.validDeltas )
{
    other.delta = nullptr;
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::~PolynomialIterator() {
    delete[] delta;
}

// Operações anexas

template< typename Coefficient >
void PolynomialIterator<Coefficient>::start( double start ) {
    t = start;
    validDeltas = 0;
}

template< typename Coefficient >
void PolynomialIterator<Coefficient>::step( double step ) {
    h = step;
    validDeltas = 1; // Não alteramos o ponto atual
}

template< typename Coefficient >
PolynomialIterator<Coefficient>::operator double() const {
    return t;
}

// Funcionalidade principal

template< typename Coefficient >
Coefficient PolynomialIterator<Coefficient>::operator*() const {
    if( validDeltas == 0 ) {
        delta[0] = p( t );
        validDeltas = 1;
    }
    return delta[0];
}

template< typename Coefficient >
void PolynomialIterator<Coefficient>::operator++() {
    t += h;
    if( p.degree() + 1 == validDeltas )
        // Aqui, já fizemos todo o trabalho pesado: basta atualizar os deltas.
        for( int i = validDeltas - 1; i > 0; --i )
            delta[i-1] = delta[i-1] + delta[i];
    else {
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
        ++validDeltas;
    }
}

} // namespace Math

#endif // POLYNOMIAL_ITERATOR_METHODS_H
