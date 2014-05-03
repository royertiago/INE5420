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
class Matrix {
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

public:
    /* Constrói a matriz com todos os valores nulos. */
    Matrix();

    /* Pequena gambiarra para permitir uma sintaxe mais agradável
     * na inicialização de vetores. Desta forma, construções como
     *  Vector<2> p = {1.1, 2.5};
     * são possíveis.
     * Construtor disponível apenas para N == 1.
     * Valores extra serão descartados, valores faltantes serão
     * preenchidos com 1.0; ver math/point.h */
    Matrix( std::initializer_list< double > );

    /* Permite inicialização de matrizes de tamanho arbitrário.
     * Posições faltantes serão inicalizadas para zero. */
    Matrix( std::initializer_list< std::initializer_list<double> > );

    /* Posições disponíveis serão preenchidas e as demais inicializadas
     * com 0, exceto a posição P-1,Q-1, que será inicializada com 1.
     * Ver math/point.h e math/linearOperator.h; este último requerimento
     * permite que uma matriz NxN seja convertida implicitamente para
     * um operador linear de ordem N, e que um vetor de ordem N seja
     * convertido implicitamente para um ponto de ordem N. */
    template< int P, int Q >
    Matrix( const Matrix<P, Q>& );

    Matrix( const Matrix<M, N>& ) = default;
    Matrix( Matrix&& ) = default;
    Matrix<M, N>& operator=( const Matrix<M, N>& ) = default;
    Matrix<M, N>& operator=( Matrix<M, N>&& ) = default;
    ~Matrix() = default;

    /* Retorna um objeto proxy que representa a linha da matriz do
     * índice especificado. Este objeto também sobrecarrega operator[],
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
     * não funciona como esperado; use
     *  printf("%lf\n", vector[7][0] ). */
    ConstMatrixLine<N> operator[]( size_t line ) const;
    MatrixLine<N> operator[]( size_t line );

    /* Informa a quantidade de linhas/colunas da matriz. */
    int rows() const;
    int columns() const;

    /* Computa o quadrado da norma de Frobenius desta matriz.
     * Para vetores, a norma de Frobenius é equivalente à
     * norma euclidiana. */
    double sqnorm() const;

    /* Matrizes são a representação computacional perfeita
     * para transformações lineares. Aqui, trataremos-nas
     * como sinônimos. */
    template <int P>
    Matrix< M, P > transform( const Matrix<N, P>& ) const;
    template <int P>
    Matrix< M, P > operator()( const Matrix<N, P>& ) const;
    
    /* Compõe esta matriz com a matriz passada. As operações comportar-
     * -se-ão como se os objetos passados sejam dados antes à transformação
     * linear tr e o resultado alimentado esta transformação; isto é,
     * a transformação passada vai ficar "na frente" desta. */
    void frontComposeWith( const Matrix<N, N>& tr );

    /* Compõe a matriz passada com esta matriz. As operações comportar-
     * -se-ão como se os vetores passados sejam dados a esta transformação
     *  linear e o resultado entregue à transformação tr; isto é,
     *  a transformação passada vai ficar "atrás" desta. */
    void backComposeWith( const Matrix<M, M>& tr );
    
    /* Operador unário -; retorna uma matriz com os mesmos valores
     * desta, mas com sinal trocado. */
    Matrix<M, N> operator-() const;
};

//      Implementações


// Construtores
template< int M, int N >
Matrix<M, N>::Matrix() {
    for( int i = 0; i < M; ++i )
        for( int j = 0; j < N; ++j )
            values[i][j] = 0.0;
}

template< int M, int N >
Matrix<M, N>::Matrix( std::initializer_list< double > source ) {
    static_assert( N == 1, "Construtor disponível apenas para vetores." );
    int i = 0;
    auto it = source.begin();
    for( ; i < M && it != source.end(); ++i, ++it )
        values[i][0] = *it;
    for( ; i < M; ++i )
        values[i][0] = 1.0;
}

template< int M, int N >
Matrix<M, N>::Matrix( std::initializer_list<std::initializer_list<double>> a) {
    auto it = a.begin();
    int i = 0;
    for( ; it != a.end() && i < M; ++i, ++it ) {
        auto jt = it->begin();
        int j = 0;
        for( ; jt != it->end() && j < N; ++j, ++jt )
            values[i][j] = *jt;
        for( ; j < N; ++j )
            values[i][j] = 0.0;
    }
    for( ; i < M; ++i )
        for( int j = 0; j < N; ++j )
            values[i][j] = 0.0;
}

template< int M, int N > template< int P, int Q >
Matrix<M, N>::Matrix( const Matrix<P, Q>& source ) {
    int i = 0;
    for( ; i < M && i < P; ++i ) {
        int j = 0;
        for( ; j < N && j < Q; ++j )
            values[i][j] = source[i][j];
        for( ; j < N; ++j )
            values[i][j] = 0.0;
    }
    for( ; i < M; ++i )
        for( int j = 0; j < N; ++j )
            values[i][j] = 0.0;
    if( M > P ) // Se sobraram linhas
        values[M-1][N-1] = 1.0;
}

// Acesso a dados (getters and setters)
template< int M, int N >
ConstMatrixLine<N> Matrix<M, N>::operator[]( size_t line ) const {
    return ConstMatrixLine<N>( values[line] );
}

template< int M, int N >
MatrixLine<N> Matrix<M, N>::operator[]( size_t line ) {
    return MatrixLine<N>( values[line] );
}

template< int M, int N >
int Matrix<M, N>::rows() const {
    return M;
}

template< int M, int N >
int Matrix<M, N>::columns() const {
    return N;
}

template< int M, int N >
double Matrix<M, N>::sqnorm() const {
    double norm = 0;
    for( int i = 0; i < M; ++i )
        for( int j = 0; j < N; ++j )
            norm += values[i][j] * values[i][j];
    return norm;
}

// Transformações de elementos
template< int M, int N > template< int P >
Matrix<M, P> Matrix<M, N>::transform( const Matrix<N, P>& rhs ) const {
    return *this * rhs;
}

template< int M, int N > template< int P >
Matrix<M, P> Matrix<M, N>::operator()( const Matrix<N, P>& rhs ) const {
    return transform( rhs );
}

// Composição
template< int M, int N >
void Matrix<M, N>::frontComposeWith( const Matrix<N, N>& op ) {
    *this = *this * op;
}

template< int M, int N >
void Matrix<M, N>::backComposeWith( const Matrix<M, M>& op ) {
    *this = op * *this;
}

// Operações algébricas

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

template< int M, int N >
Matrix<M, N> operator-( const Matrix<M, N>& lhs, const Matrix<M, N>& rhs ) {
    Matrix<M, N> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] - rhs[i][j];
    return r;
}

template< int M, int N >
Matrix<M, N> operator*( const Matrix<M, N>& lhs, double rhs ) {
    Matrix<M, N> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = lhs[i][j] * rhs;
    return r;
}

template< int M, int N >
Matrix<M, N> Matrix<M, N>::operator-() const {
    Matrix<M, N> r;
    for( int i = 0; i < M; i++ )
        for( int j = 0; j < N; j++ )
            r[i][j] = -values[i][j];
    return r;
}

} //namespace Math

#endif // MATRIX_H
