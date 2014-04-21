/* declarationMacros.h
 * Contém definições de macros que auxiliam a criação de testes 
 * e adição automática à lista de testes, em testList.h.
 *
 * Todas as macros possuem por parâmetro o nome da função que vai
 * executar o teste; estes nomes devem ser únicos, em todo o programa
 * sendo testado. */
#ifndef DECLARATION_MACROS_H
#define DECLARATION_MACROS_H

#include "testList.h"

/* Registra a função de teste na lista de testes.
 * Use esta macro fora de qualquer escopo, sem um ponto-e-vírgula
 * terminal, assim:
 *
 *  bool minhaFuncaoDeTesteFofinha() {
 *      // código
 *  }
 *  REGISTER_TEST( minhaFuncaoDeTesteFofinha )
 *
 * A adição do teste à lista de testes se dá antes da execução do main.
 */
#define REGISTER_TEST( test )                                           \
namespace Test {                                                        \
    struct TEST_ADDER_ ## test {                                        \
        TEST_ADDER_ ## test () {                                        \
            Test::addTest( test, #test, __FILE__ );                     \
        }                                                               \
    };                                                                  \
    const static TEST_ADDER_ ## test instance = TEST_ADDER_ ## test (); \
}

/* Declara um teste e o adiciona à lista de testes.
 * Use esta macro fora de qualquer escopo.
 * Após esta macro, deve vir o código da função de teste; assim:
 *
 *  DECLARE_TEST( meuTesteFofinho ) {
 *      // código
 *      return true;
 *  }
 * 
 * A adição do teste à lista de testes se dá antes da execução do main.
 */
#define DECLARE_TEST( test )                                            \
bool test();                                                            \
REGISTER_TEST( test )                                                   \
bool test()

#endif // DECLARATION_MACROS_H
