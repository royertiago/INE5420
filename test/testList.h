/* testList.h
 * Duan funções que permitem uma organização de uma lista de testes.
 * Esta classe possui uma única instância, oculta (singleton);
 * para acessar as funcionalidades desta classe, utilize os
 * métodos estáticos.
 */
#ifndef TEST_LIST_H
#define TEST_LIST_H

#include "testFunction.h"

namespace Test {

    /* Adiciona um teste para ser executado. */
    void addTest( TestFunction );

    /* Executa todos os testes especificados.
     * Retorna true caso todos os testes tenham suceido,
     * false caso contrário. */
    bool run();

} // namespace Test

#endif // TEST_LIST_H
