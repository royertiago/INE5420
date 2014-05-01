/* testMacro.h
 * Macro que auxilia a chamada de métodos de teste.
 *
 * Todos os métodos de teste de igualdade obedecem à seguinte
 * assinatura:
 *  bool testEquals( T, T, const char *, int )
 * Os dois primeiros campos correspondem ao valor real e ao valor
 * esperado, respectivamente. O terceiro parâmetro é o trecho de
 * código que gerou o valor a ser testado, e o último é a linha
 * do código-fonte em que este valor foi gerado.
 *
 * A macro cria os dois últimos campos automaticamente:
 *  Test::TEST_EQUALS( x + y, 4 )
 * é expandido para
 *  Test::testEquals( x + y, 4, "x + y", __LINE__ )
 *
 * Note que, como é uma macro, não há resolução de escopo.
 */
#ifndef TEST_MACRO_H
#define TEST_MACRO_H

#define TEST_EQUALS( testedCode, expectedValue ) \
    testEquals( testedCode, expectedValue, #testedCode, __LINE__ )

#endif // TEST_MACRO_H
