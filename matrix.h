/* matrix.h
 * Este arquivo contém classes, no namespace Math, que representam
 * matrizes e vetores e são capazes de efetuar operações com eles.
 *
 * As matrizes internas destas classes utilizam double. Os valores
 * internos da matriz podem ser acessados diretamente, através do
 * operator().
 *
 * Caso a matriz seja unidimensional (isto é, uma de suas dimensões
 * possui valor 1), uma versão sobrecarregada do operator() que
 * toma apenas um argumento estará disponível para uso.
 *
 * Parâmetros do template:
 *  M - quantidade de linhas
 *  N - quantidade de colunas
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <type_traits> //SFINAE em operator()

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
    Matrix& operator=( const Matrix& ) = default;
    Matrix& operator=( Matrix&& ) = default;
    ~Matrix() = default;

    /* Retorna uma referência para o elemento que está na linha row
     * e coluna column. */
    double& operator()( size_t row, size_t column ) {
        return values[row][column];
    }
    const double& operator()( size_t row, size_t column ) const {
        return values[row][column];
    }

    /* Retorna uma referência para o elemento que está na posição
     * especificada.
     *
     * Disponível apenas caso a matriz possua apenas uma coluna. */
    typename std::enable_if< N == 1, double& >::type 
    operator()( size_t index ) {
        return values[index][0];
    }
    typename std::enable_if< N == 1, const double& >::type
    operator()( size_t index ) const {
        return values[index][0];
    }

    template< int O, int P >
    friend Matrix<M, P> operator*( const Matrix<M, N>&, const Matrix<O, P>& );
};

/* Aqui, o fato de typedef ser não-estrito é uma propriedade bastante
 * útil: a função de multiplicação, por exemplo, toma uma matriz MxN
 * e outra NxP e devolve uma MxP. Caso P seja 1, o valor retornado
 * será uma matriz Mx1 - o que, de acordo com a seguinte definição,
 * é um vetor: */
template <int M>
using Vector = Matrix<M, 1>;


//      Implementações


/* Implementação ingênua da multiplicação de matrizez. */
template< int M, int N, int O, int P >
Matrix<M, P> operator*( const Matrix<M, N>& lhs, const Matrix<O, P>& rhs ) {
    static_assert( N == O, "Dimensões internas incompatíveis." );
    Matrix<M, P> r; //retorno
    for( int i = 0; i < M; i++ ) {
        for( int j = 0; j < P; j++ ) {
            r(i,j) = 0.0;
            for( int k = 0; k < N; k++ )
                r(i,j) += lhs(i,j) * rhs(i,j);
        }
    }
    return r;
}

} //namespace Math

#endif // MATRIX_H
