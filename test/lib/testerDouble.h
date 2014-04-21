/* testerDouble.h
 * Classe que testa igualdade de valores em ponto flutuante
 * (precisão dupla) que tolera uma quantidade definida pelo
 * usuário de erro.
 */
#ifndef TESTER_DOUBLE_H
#define TESTER_DOUBLE_H

namespace Test {

class TesterDouble {
    double epsilon;

public:
    /* Constrói o testador de doubles com a precisão passada. */
    explicit TesterDouble( double epsilon );

    /* Constrói o testador de doubles com precisão do epsilon
     * de máquina. */
    TesterDouble();

    /* Constrói o testador com um múltiplo do epsilon de máquina. */
    explicit TesterDouble( int );

    /* Altera o epsilon do testador. */
    void setEpsilon( double epsilon );

    /* Determina se a diferença entre o valor atual e o valor
     * esperado é inferior ao epsilon especificado.
     * Caso seja, a função retorna true; caso contrário, a função
     * imprime uma mensagem de erro na tela e retorna false.
     *
     * A "assinatura" deste método é compatível com a da função
     * Test::testEquals, de testFunction.h; portanto, a macro
     * TEST_EQUALS também pode ser usada aqui.
     *
     * actualValue   é o valor que o código de teste produz.
     * expectedValue é o valor esperado para aquele trecho de código.
     * lineText      é o trecho de código que está sendo testado.
     * lineNumber    é o número da linha em que este teste foi executado.
     */
    bool testEquals( double actualValue, double expectedValue,
            const char * lineText, int lineNumber );
};

} // namespace Test

#endif // TESTER_DOUBLE_H
