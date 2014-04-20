/* testFunction.h
 * Typedef da assinatura das funções de testes.
 */
#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H

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

} // namespace Test
#endif // TEST_FUNCTION_H
