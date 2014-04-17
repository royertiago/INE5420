/* matrixLine.h
 * Classe que representa uma linha de uma matriz.
 *
 * Permite acesso aos elementos individuais de uma matriz
 * de forma semelhante ao proxy pattern.
 *
 * Implementa operator[] para todos os parâmetros de N, 
 * mas conversão implícita e atribuição só estão disponíveis
 * para N = 1.
 *
 * São duas implementações: MatrixLine e ConstMatrixLine. A primeira
 * permite modificar os elementos da matriz original; a segunda,
 * apenas lê-los.
 */

#ifndef MATRIX_LINE_H
#define MATRIX_LINE_H

#include <array>

namespace Math {

template< int N >
struct MatrixLine {
    std::array< double, N > & line;

    /* Constrói uma MatrixLine que referencia o array especificado.
     * Note que esta classe pode modificar a linha passada. */
    MatrixLine( std::array< double, N > & line );

    /* Retorna uma referência para o índice especificado. */
    double & operator[]( size_t index );
    const double & operator[]( size_t index ) const;

    /* Retorna o valor do primeiro elemento da linha.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    operator double();

    /* Altera o valor do primeiro elemento da linha e retorna
     * uma referência para este elemento.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    double & operator=( double d );

    /* Divide o valor do primeiro elemento da linha por d e retorna
     * uma referência para este elemento.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    double & operator/=( double d );

    /* Copia a linha passada para esta. */
    MatrixLine<N>& operator=( const MatrixLine& );
};

template< int N >
struct ConstMatrixLine {
    std::array< double, N > const & line;

    /* Constrói uma ConstMatrixLine que referencia o array especificado.
     * Esta classe não pode modificar a linha passada. */
    ConstMatrixLine( std::array< double, N > const & line );

    /* Retorna uma referência para o índice especificado. */
    const double& operator[]( size_t index ) const;

    /* Retorna o valor do primeiro elemento da linha.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    operator double();
};

//Implementações de MatrixLine

template< int N >
MatrixLine<N>::MatrixLine( std::array<double, N>& line ):
    line( line )
{}

template< int N >
double& MatrixLine<N>::operator[]( size_t index ) {
    return line[index];
}

template< int N >
const double& MatrixLine<N>::operator[]( size_t index ) const {
    return line[index];
}

template< int N >
MatrixLine<N>::operator double() {
    static_assert( N == 1, "operator double() disponível apenas para N == 1" );
    return line[0];
}

template< int N >
double& MatrixLine<N>::operator=( double d ) {
    static_assert( N == 1, "operator=(double) disponível apenas para N == 1" );
    return line[0] = d;
}

template< int N >
double& MatrixLine<N>::operator/=( double d ) {
    static_assert( N == 1, "operator=(double) disponível apenas para N == 1" );
    return line[0] /= d;
}

template< int N >
MatrixLine<N>& MatrixLine<N>::operator=( const MatrixLine<N> & m ) {
    line = m.line;
    return *this;
}

//Implementações de ConstMatrixLine

template< int N >
ConstMatrixLine<N>::ConstMatrixLine( std::array<double, N> const & line ):
    line( line )
{}

template< int N >
const double& ConstMatrixLine<N>::operator[]( size_t index ) const {
    return line[index];
}

template< int N >
ConstMatrixLine<N>::operator double() {
    static_assert( N == 1, "operator double() disponível apenas para N == 1" );
    return line[0];
}

} // namespace Math

#endif // MATRIX_LINE_H
