/* testerMatrix.h
 * Classe que testa igualdade de matrizes sobre doubles
 * com tolerância a imprecisões do ponto flutuante.
 */
#ifndef TESTER_MATRIX_H
#define TESTER_MATRIX_H

#include <cstdio>

namespace Test {

class TesterMatrix {
    double epsilon;

public:
    /* Constrói um testador de matrizes com a precisão passada. */
    explicit TesterMatrix( double epsilon );

    /* Constrói um testador com precisão do epsilon de máquina. */
    TesterMatrix();

    /* Constrói um testado com um múltiplo do epsilon de máquina. */
    explicit TesterMatrix( int );
    

    /* Altera a precisão do testador. */
    void setEpsilon( double epsilon );

    /* Determina se a diferença entre a matriz obtida e a matriz
     * esperada é pequena, de acordo com o TesterDouble deste objeto.
     * Caso seja, a função retorna true; caso contrário, a função
     * imprime uma mensagem de erro na tela e retorna false.
     *
     * Este objeto testa se as matrizes passadas possuem mesmas
     * dimensões e se todos os elementos da matriz obtida diferirem
     * menos de epsilon do valor correspondente na matriz esperada.
     *
     * Note que este método é um template: ele aceita diversos
     * tipos de matrizes para fazer a comparação. As exigências são:
     *  - matrix.operator[].operator[] existe e retorna um tipo
     *  convertível para double;
     *  - matrix.rows() e matrix.columns() existem e retornam,
     *  respectivamente, as linhas e colunas da matriz;
     *  - Todos estes métodos são executáveis em matrizes constantes.
     * O método pode trabalhar com tipos diferentes de matrizes,
     * basta que ambas suportem as operações acima.
     *
     * A assinatura é compatível com a macro TEST_EQUALS, de testMacro.h.
     *
     * actualValue   é o valor que o código de teste produz.
     * expectedValue é o valor esperado para aquele trecho de código.
     * lineText      é o trecho de código que está sendo testado.
     * lineNumber    é o número da linha em que este teste foi executado.
     */
    template< typename M1, typename M2 >
    bool testEquals( const M1& actualMatrix, const M2& expectedMatrix,
            const char * lineText, int lineNumber ) const;

protected:
    /* Função auxiliar. Executa o teste de precisão da matriz;
     * retorna true caso esteja dentro da tolerância especificada,
     * retorna false e imprime uma mensagem de erro caso contrário.
     *
     * actualValue   é o valor que o código de teste produz.
     * expectedValue é o valor esperado para aquele trecho de código.
     * lineText      é o trecho de código que está sendo testado.
     * lineNumber    é o número da linha em que este teste foi executado.
     * row           é a linha da matriz em que se encontra o valor testado.
     * column        é a coluna da matriz em que se encontra o valor testado.
     */
    bool testDouble( double actual, double expected, const char * lineText,
            int lineNumber, int row, int column ) const;
};

// Implementação do método templatizado
template< typename M1, typename M2 >
bool TesterMatrix::testEquals( const M1& actual, const M2& expected,
        const char * l, int n ) const
{
    using std::printf;
    bool b = true; // Valor de retorno
    
    if( actual.rows() != expected.rows() ) {
        printf( "%s\nat line %i - Rows do not match "
                "with expected matrix\n\n", l, n );
        b = false;
    }

    if( actual.columns() != expected.columns() ) {
        printf( "%s\nat line %i - Columns do not match "
                "with expected matrix\n\n", l, n );
        b = false;
    }

    for( int i = 0; i < actual.rows(); ++i )
        for( int j = 0; j < actual.columns(); ++j )
            b &= testDouble( actual[i][j], expected[i][j], l, n, i, j );

    return b;
}

} // namespace Test

#endif // TESTER_MATRIX_H
