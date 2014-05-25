/* affineTester.h
 * Classe que testa igualdade entre operadores afins, sob
 * detetrminada precisão.
 */
#ifndef AFFINE_TESTER_H
#define AFFINE_TESTER_H

#include <string>
#include "math/affineOperator.h"
#include "test/lib/testerMatrix.h"

namespace Test {

class AffineTester {
    TesterMatrix t;

public:
    /* Constrói um testador com precisão do epsilon de máquina. */
    AffineTester() = default;

    /* Constrói um testador de operadores afins com um últiplo do
     * epsilon de máquina. */
    explicit AffineTester( int );

    /* Altera a precisão do testador. */
    void setEpsilon( double );

    /* Determina se a diferença entre o operador afim obtido e
     * o operador esperado é pequena, de acordo com o TesterMatrix
     * deste objeto.
     *
     * Este objeto testa proximidade entre os dois componentes
     * do operador afim, usando o TesterMatrix; para mais informações,
     * ver test/lib/testerMatrix.h.
     * A assinatura é compatível com a macro TEST_EQUALS, de testMacro.h.
     *
     * actualOperator   é o valor que o código de teste produz.
     * expectedOperator é o valor esperado para aquele trecho de código.
     * lineText         é o trecho de código que está sendo testado.
     * lineNumber       é o número da linha em que este teste foi executado.
     */
    template< int N >
    bool testEquals( const Math::AffineOperator<N>& actualOperator,
                     const Math::AffineOperator<N>& expectedOperator,
                     const char * lineText, int lineNumber ) const;
};

// Implementação do método templatizado
template< int N >
bool AffineTester::testEquals( const Math::AffineOperator<N>& actual,
                               const Math::AffineOperator<N>& expected,
                               const char * lineText, int lineNumber ) const
{
    std::string stm( lineText );
    std::string stv( lineText );
    stm += ".m";
    stv += ".v";
    return t.testEquals( actual.m, expected.m, stm.c_str(), lineNumber )
        && t.testEquals( actual.v, expected.v, stv.c_str(), lineNumber );
}

} // namespace Test

#endif // AFFINE_TESTER_H
