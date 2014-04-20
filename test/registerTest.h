/* registerTest.h
 * Contém definições de macros que adicionam testes à TestList
 * automaticamente. */
#ifndef REGISTER_TEST_H
#define REGISTER_TEST_H

#include "testList.h"

/* Registra a função de teste test na lista de testes.
 * Use esta macro fora de qualquer escopo, sem um ponto-e-vírgula
 * terminal. */
#define REGISTER_TEST( test )                                           \
namespace Test {                                                        \
    struct TEST_ADDER_ ## test {                                        \
        TEST_ADDER_ ## test () {                                        \
            Test::addTest( test );                                      \
        }                                                               \
    };                                                                  \
    const static TEST_ADDER_ ## test instance = TEST_ADDER_ ## test (); \
}

#endif // REGISTER_TEST_H
