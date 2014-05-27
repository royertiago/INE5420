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

#include "polynomialIterator.h" // Exceção; ver polynomialIteratorMethods.h
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <utility> //std::swap
#include <cstddef> //std::size_t

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

    /* Constrói um iterador para este polinômio.
     * t é o ponto inicial de iteração,
     * d é o incremento.
     * Não modifique o polinômio enquanto o iterador for necessário. */
    PolynomialIterator<Coefficient> iterator( double t, double d ) const;

    /* Multiplicação de polinômios.
     * Note que multiplicação por polinômios sobre double sempre faz
     * sentido; é equivalente à multiplicar por um escalar que se
     * altera. */
    Polynomial<Coefficient> operator*( const Polynomial<double>& ) const;

    Polynomial<Coefficient> operator+( const Polynomial<Coefficient>& ) const;
    friend class Polynomial<double>; // Para uso no operator*
};

} // namespace Math

#include "polynomialMethods.h"

#endif // POLYNOMIAL_H
