/* matrix.h
 * Este arquivo contém classes que representam matrizes bidimensionais.
 *
 * As matrizes internas destas classes utilizam double. Os valores
 * internos da matriz podem ser acessados diretamente, através do
 * operator[]. A primeira invocação de operator[] retorna uma MatrixLine;
 * este objeto, por sua vez, pode ter seu operator[] invocado para obter
 * o valor desejado.
 * Isto é, comandos como matrix[5][7] = 5 tem o efeito esperado.
 *
 * Caso a matriz seja unidimensional (isto é, uma de suas dimensões
 * possui valor 1), o objeto MatrixLine pode ser usado para modificar
 * o valor da linha diretamente.
 *
 * Parâmetros do template:
 *  M - quantidade de linhas
 *  N - quantidade de colunas
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include "matrixLine.h"

namespace Math {

template< int M, int N >
struct Matrix {
    /* Lista de [v]alores da matriz.
     *
     * Note que as dimensões parecem "invertidas".  M representa
     * a quantidade de linhas e N a de colunas; ao escrever algo como
     *  abraham[lin][col]
     * o compilador agrupa isso como
     *  ( abraham.operator[](lin) ).operator[](col)
     * Queremos que lin seja limitado por M, portanto, M deve ir
     * no template externo - mesmo que pareça invertido na declaração. */
    std::array< std::array<double, N>, M > values;

    Matrix() = default;
    Matrix( const Matrix& ) = default;
    Matrix( Matrix&& ) = default;
    Matrix<M, N>& operator=( const Matrix<M, N>& ) = default;
    Matrix<M, N>& operator=( Matrix<M, N>&& ) = default;

    /* Pequena gambiarra para permitir uma sintaxe mais agradável
     * na inicialização de vetores. Desta forma, construções como
     *  Vector<2> p = {1.1, 2.5};
     * são possíveis.
     * Construtor disponível apenas para N == 1.
     * Valores extra serão descartados, valores faltantes serão
     * preenchidos com zeros. */
    Matrix( std::initializer_list< double > a );

    ~Matrix() = default;

    /* Retorna um objeto proxy que representa a linha da matriz
     * de índice line. Este objeto também sobrecarrega o operator[],
     * portanto é possível usar chamadas como
     *  matrix[2][5]
     * para acessar o elemento da terceira linha e sexta coluna
     * diretamente.
     *
     * Note que o endereçamento é feito a partir do zero.
     *
     * Caso N seja 1, MatrixLine<N> suporta operações semelhantes
     * às do tipo nativo double, fazendo com que
     *  vector[7] = 4;
     * seja um código válido que faça o que ele aparentemente faz.
     *
     * Entretanto, para permitir que estas modificações sejam
     * propagadas na matriz originária, objetos desta classe devem 
     * manter ponteiros para as linhas da classe. Isto é, vector[7]
     * não é apenas um double. Portando, código como 
     *  printf("%lf\n", vector[7] );
     * não funciona como esperado. 
     *
     * Aparentemente, 
     *  printf("%lf\n", vector[7][0] );
     * produz o resultado esperado (e similarmente para matrizes);
     * não sei o porquê deste comportamento, entretanto. */
    ConstMatrixLine<N> operator[]( size_t line ) const {
        return ConstMatrixLine<N>( values[line] );
    }

    MatrixLine<N> operator[]( size_t line ) {
        return MatrixLine<N>( values[line] );
    }
    
    /* Operador unário -; retorna uma matriz com os mesmos valores
     * desta, mas com sinal trocado. */
    Matrix<M, N> operator-() {
        Matrix<M, N> r;
        for( int i = 0; i < M; i++ )
            for( int j = 0; j < N; j++ )
                r[i][j] = -values[i][j];
        return r;
    }
};

//      Implementações

template< int M, int N >
Matrix<M, N>::Matrix( std::initializer_list< double > source ) {
    static_assert( N == 1, "Construtor disponível apenas para vetores." );
    int i = 0;
    auto it = source.begin();
    for( ; i < M && it != source.end(); ++i, ++it )
        values[i][0] = *it;
    for( ; i < M; ++i )
        values[i][0] = 0;
}

/* Implementação ingênua da multiplicação de matrizez. */
template< int M, int N, int O, int P >
Matrix<M, P> operator*( const Matrix<M, N>& lhs, const Matrix<O, P>& rhs ) {
    static_assert( N == O, "Dimensões internas incompatíveis." );
    Matrix<M, P> r; //retorno
    for( int i = 0; i < M; i++ ) {
        for( int j = 0; j < P; j++ ) {
            r[i][j] = 0.0;
            for( int k = 0; k < N; k++ )
                r[i][j] += lhs[i][k] * rhs[k][j];
        }
    }
    return r;
}

template< int M, int N >
Matrix<M, N> operator+( const Matrix<M, N>& lhs, const Matrix<M, N>& rhs ) {
    Matrix<M, N> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] + rhs[i][j];
    return r;
}

} //namespace Math

#endif // MATRIX_H
