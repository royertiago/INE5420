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
     * são possíveis. */
    Matrix( std::array< double, M > a ) {
        static_assert( N == 1, "Construtor disponível apenas para vetores." );
        for( int i = 0; i < M; i++ )
            values[i][0] = a[0];
    }

    ~Matrix() = default;

    //TODO: documentar
    ConstMatrixLine<N> operator[]( size_t column ) const {
        return ConstMatrixLine<N>( values[column] );
    }

    MatrixLine<N> operator[]( size_t column ) {
        return MatrixLine<N>( values[column] );
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
