/* matrix.h
 * Classes que representam matrizes bidimensionais.
 *
 * As matrizes têm suas entradas templatizadas; as entradas das matrizes
 * podem ter qualquer tipo. Entretanto, é necessário que estejam definidos
 *  operator+(const T&, const T&);
 *  operator-(const T&, const T&);
 *  operator-(const T&);
 *  operator*(const T&, double);
 *  operator*(double, const T&);
 *  operator=(const T&).
 *
 * Pode ocorrer multiplicação de matrizes de tipos diferentes, mas não soma.
 *
 * Os valores internos da matriz podem ser acessados diretamente, através do
 * operator[]. A primeira invocação de operator[] retorna uma MatrixLine;
 * este objeto, por sua vez, pode ter seu operator[] invocado para obter
 * o valor desejado.
 * Isto é, comandos como matrix[5][7] = 5 tem o efeito esperado.
 *
 * Caso a matriz seja unidimensional (isto é, suas segunda dimensão
 * possui valor 1), o objeto MatrixLine pode ser usado para modificar
 * o valor da linha diretamente.
 *
 * Parâmetros do template:
 *  M - quantidade de linhas
 *  N - quantidade de colunas
 *  T - tipo sobre o qual a matriz será construída.
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include "matrixLine.h"

namespace Math {

template< int M, int N, typename T = double >
class Matrix {
    /* Lista de valores da matriz. */
    std::array< std::array<T, N>, M > values;

public:
    /* Constrói a matriz com todos os valores T(). */
    Matrix();

    /* Pequena gambiarra para permitir uma sintaxe mais agradável
     * na inicialização de vetores. Desta forma, construções como
     *  Vector<2> p = {1.1, 2.5};
     * são possíveis.
     * Construtor disponível apenas para N == 1.
     * Valores extra serão descartados, valores faltantes serão
     * preenchidos com T(). */
    Matrix( std::initializer_list< T > );

    /* Permite inicialização de matrizes de tamanho arbitrário.
     * Posições faltantes serão inicalizadas para T(). */
    Matrix( std::initializer_list< std::initializer_list<T> > );

    /* Retorna uma matriz cujas entradas na diagonal principal
     * serão o valor T(1.0) e nas demais entradas T().
     * Para T == double, isto corresponde à matriz identidade. */
    static Matrix<M, N, T> identity();


    /* Retorna um objeto proxy que representa a linha da matriz do
     * índice especificado. Este objeto também sobrecarrega operator[],
     * portanto é possível usar chamadas como
     *  matrix[2][5]
     * para acessar o elemento da terceira linha e sexta coluna
     * diretamente.
     *
     * Note que o endereçamento é feito a partir do zero.
     *
     * Caso N seja 1, MatrixLine<N, T> suporta conversão implícita
     * para T e atribuição, fazendo com que
     *  vector[7] = 4 + vector[8];
     * seja um código válido que faça o que ele aparentemente faz.
     *
     * Entretanto, para permitir que estas modificações sejam
     * propagadas na matriz original, objetos desta classe devem 
     * manter ponteiros para as linhas da classe. Isto é, vector[7]
     * não é apenas um T. Portanto, código como 
     *  printf("%lf\n", vector[7] );
     * não funciona como esperado; use
     *  printf("%lf\n", vector[7][0] ). */
    ConstMatrixLine<N, T> operator[]( size_t line ) const;
    MatrixLine<N, T> operator[]( size_t line );

    /* Informa a quantidade de linhas/colunas da matriz. */
    int rows() const;
    int columns() const;
};
// Operadores disponíveis

/* Soma de matrizes.
 * As dimensões devem ser as mesmas. */
template< int M, int N, typename T >
Matrix<M, N, T> operator+( const Matrix<M, N, T>&, const Matrix<M, N, T>& );

/* Operador unário -; retorna uma matriz com os mesmos valores
 * desta, mas com sinal trocado. Operator-(T&) deve estar
 * definido. */
template< int M, int N, typename T >
Matrix<M, N, T> operator-( const Matrix<M, N, T>& );

/* Subtração de matrizes.
 * operator-( const T&, const T& ) deve estar definido. */
template< int M, int N, typename T >
Matrix<M, N, T> operator-( const Matrix<M, N, T>&, const Matrix<M, N, T>& );

/* Multiplicação por escalar.
 * operator*( const T&, const U& ) deve estar definido. */
template< int M, int N, typename T, typename U >
auto operator*( const Matrix<M, N, T>& lhs, const U& rhs ) ->
    Matrix<M, N, decltype( lhs[0][0] * rhs )>;
template< int M, int N, typename T, typename U >
auto operator*( const U& lhs, const Matrix<M, N, T>& rhs ) ->
    Matrix<M, N, decltype( rhs[0][0] * lhs )>;

/* Multiplicação de matrizes.
 * A multiplicação é feita usando o algoritmo trivial. Para
 * que a multiplicação entre os tipos T e U seja possível,
 * operator*( const T&, const U& ) deve estar definido.
 * Note que N == O. */
template< int M, int N, typename T, int O, int P, typename U >
auto operator*( const Matrix<M, N, T>& lhs, const Matrix<O, P, U>& rhs )
    -> Matrix<M, P, decltype( lhs[0][0] * rhs[0][0] )>;

/* Multiplicação por inverso de escalar.
 * operator/( const T&, const U& ) deve estar definido. */
template< int M, int N, typename T, typename U >
auto operator/( const Matrix<M, N, T>& lhs, const U& rhs ) ->
    Matrix<M, N, decltype( lhs[0][0] * rhs )>;

// Implementação

// Construtores
template< int M, int N, typename T >
Matrix<M, N, T>::Matrix() {
    for( int i = 0; i < M; ++i )
        for( int j = 0; j < N; ++j )
            values[i][j] = T();
}

template< int M, int N, typename T >
Matrix<M, N, T>::Matrix( std::initializer_list< T > source ) {
    static_assert( N == 1, "Construtor disponível apenas para vetores." );
    int i = 0;
    auto it = source.begin();
    for( ; i < M && it != source.end(); ++i, ++it )
        values[i][0] = *it;
    for( ; i < M; ++i )
        values[i][0] = T();
}

template< int M, int N, typename T >
Matrix<M, N, T>::Matrix( std::initializer_list<std::initializer_list<T>> a)
{
    auto it = a.begin();
    int i = 0;
    for( ; it != a.end() && i < M;  ++i, ++it ) {
        auto jt = it->begin();
        int j = 0;
        for( ; jt != it->end() && j < N;  ++j, ++jt )
            values[i][j] = *jt;
        for( ; j < N; ++j )
            values[i][j] = T();
    }
    for( ; i < M; ++i )
        for( int j = 0; j < N; ++j )
            values[i][j] = T();
}

// Acesso a dados (getters and setters)
template< int M, int N, typename T >
ConstMatrixLine<N, T> Matrix<M, N, T>::operator[]( size_t line ) const {
    return ConstMatrixLine<N, T>( values[line] );
}

template< int M, int N, typename T >
MatrixLine<N, T> Matrix<M, N, T>::operator[]( size_t line ) {
    return MatrixLine<N, T>( values[line] );
}

template< int M, int N, typename T >
int Matrix<M, N, T>::rows() const {
    return M;
}

template< int M, int N, typename T >
int Matrix<M, N, T>::columns() const {
    return N;
}

// Operações algébricas

template< int M, int N, typename T >
Matrix<M, N, T> operator+( const Matrix<M, N, T>& lhs, 
                           const Matrix<M, N, T>& rhs ) 
{
    Matrix<M, N, T> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] + rhs[i][j];
    return r;
}

template< int M, int N, typename T >
Matrix<M, N, T> operator-( const Matrix<M, N, T>& m ) {
    Matrix<M, N, T> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = -m[i][j];
    return r;
}

template< int M, int N, typename T >
Matrix<M, N, T> operator-( const Matrix<M, N, T>& lhs, 
                           const Matrix<M, N, T>& rhs ) {
    Matrix<M, N, T> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] - rhs[i][j];
    return r;
}

template< int M, int N, typename T, int O, int P, typename U >
auto operator*( const Matrix<M, N, T>& lhs, const Matrix<O, P, U>& rhs )
    -> Matrix<M, P, decltype( lhs[0][0] * rhs[0][0] )>
{
    static_assert( N == O, "Dimensões internas incompatíveis." );
    typedef decltype( lhs[0][0] * rhs[0][0] ) V;
    Matrix<M, P, V> r; //retorno
    for( int i = 0; i < M; i++ ) {
        for( int j = 0; j < P; j++ ) {
            r[i][j] = V();
            for( int k = 0; k < N; k++ )
                r[i][j] = r[i][j] + lhs[i][k] * rhs[k][j];
        }
    }
    return r;
}

template< int M, int N, typename T, typename U >
auto operator*( const Matrix<M, N, T>& lhs, const U& rhs )
    -> Matrix<M, N, decltype( lhs[0][0] * rhs )>
{
    Matrix<M, N, decltype( lhs[0][0] * rhs )> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] * rhs;
    return r;
}

template< int M, int N, typename T, typename U >
auto operator*( const U& lhs, const Matrix<M, N, T>& rhs )
    -> Matrix<M, N, decltype( rhs[0][0] * lhs )>
{
    return rhs * lhs;
}

template< int M, int N, typename T, typename U >
auto operator/( const Matrix<M, N, T>& lhs, const U& rhs )
    -> Matrix<M, N, decltype( lhs[0][0] * rhs )>
{
    Matrix<M, N, decltype( lhs[0][0] * rhs )> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] / rhs;
    return r;
}

// Método estático
template< int M, int N, typename T >
Matrix<M, N, T> Matrix<M, N, T>::identity() {
    Matrix<M, N, T> r;
    for( int i = 0; i < M && i < N; ++i )
        r[i][i] = T(1.0);
    return r;
}

} //namespace Math

#endif // MATRIX_H
