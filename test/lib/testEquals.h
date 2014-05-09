/* testEquals.h
 * Funções para automatização de testes.
 */

#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

namespace Test {

    /* Testa se o valor actualValue é igual ao valor expectedValue.
     * Caso seja, a função retorna true; caso contrário, a função
     * imprime uma mensagem de erro na tela e retorna false.
     *
     * A macro TEST_EQUALS, de testMacro.h, constrói os dois últimos
     * campos automaticamente.
     *
     * actualValue   é o valor que o código de teste produz.
     * expectedValue é o valor esperado para aquele trecho de código.
     * lineText      é o trecho de código que está sendo testado.
     * lineNumber    é o número da linha em que este teste foi executado.
     */
    bool testEquals( int actualValue, int expectedValue, 
            const char * lineText, int lineNumber );
    bool testEquals( double actualValue, double expectedValue, 
            const char * lineText, int lineNumber );
    bool testEquals( bool actualValue, bool expectedValue, 
            const char * lineText, int lineNumber );
    bool testEquals( const char * actualValue, const char * expectedValue,
            const char * lineText, int lineNumber );

} // namespace Test

#endif // TEST_FUNCTION_H
