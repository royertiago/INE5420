/* testList.h
 * Funções que permitem uma organização de uma lista de testes.
 * Esta classe possui uma única lista de testes; utilize as
 * funções Test::addTest e Test::run para utilizá-la.
 */
#ifndef TEST_LIST_H
#define TEST_LIST_H

namespace Test {
    /* Função de teste.
     * Uma função de teste não recebe parâmetro algum
     * (deve apenas rodar o teste) e deve informar para
     * a função se o código testado passou (true) ou não
     * (false) no teste.
     *
     * As funções de teste são encorajadas a imprimir
     * quando o código especificado passou no teste. */
    typedef bool (* TestFunction )( void );

    /* Adiciona um teste para ser executado. 
     * t    é a função que deve ser executada,
     * name é o nome do teste.
     * file é o arquivo do qual foi extraído o teste. 
     *
     * Veja em declarationMacros.h macros que automatizam o uso
     * desta função. */
    void addTest( TestFunction f, const char* name, const char * file );

    /* Executa todos os testes especificados.
     * Retorna true caso todos os testes tenham suceido,
     * false caso contrário. */
    bool run();

} // namespace Test

#endif // TEST_LIST_H
