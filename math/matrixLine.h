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

template< int N, typename T > class MatrixLine;
template< int N, typename T > class ConstMatrixLine;

template< int N, typename T >
class MatrixLine {
    std::array< T, N > & line; // Referência para a linha da matriz.

public:
    /* Constrói uma MatrixLine que referencia o array especificado.
     * Note que esta classe pode modificar a linha passada. */
    MatrixLine( std::array< T, N > & line );

    /* Retorna uma referência para o índice especificado. */
    T & operator[]( size_t index );
    const T & operator[]( size_t index ) const;

    /* Retorna o valor do primeiro elemento da linha.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    operator T() const;

    /* Altera o valor do primeiro elemento da linha e retorna
     * uma referência para este elemento.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    T & operator=( T d );

    /* Copia a linha passada para esta. */
    MatrixLine<N, T>& operator=( const MatrixLine& );
    MatrixLine<N, T>& operator=( const ConstMatrixLine< N, T >& );
};

template< int N, typename T >
class ConstMatrixLine {
    std::array< T, N > const & line;

public:
    /* Constrói uma ConstMatrixLine que referencia o array especificado.
     * Esta classe não pode modificar a linha passada. */
    ConstMatrixLine( std::array< T, N > const & line );

    /* Retorna uma referência para o índice especificado. */
    const T& operator[]( size_t index ) const;

    /* Retorna o valor do primeiro elemento da linha.
     * Disponível apenas caso haja um único valor na linha (N==1). */
    operator T() const;
};

//Implementações de MatrixLine

template< int N, typename T >
MatrixLine<N, T>::MatrixLine( std::array<T, N>& line ):
    line( line )
{}

template< int N, typename T >
T& MatrixLine<N, T>::operator[]( size_t index ) {
    return line[index];
}

template< int N, typename T >
const T& MatrixLine<N, T>::operator[]( size_t index ) const {
    return line[index];
}

template< int N, typename T >
MatrixLine<N, T>::operator T() const {
    static_assert( N==1, "Conversão implícita disponível apenas para N == 1");
    return line[0];
}

template< int N, typename T >
T& MatrixLine<N, T>::operator=( T d ) {
    static_assert( N==1, "Atribuição disponível apenas para N == 1" );
    return line[0] = d;
}

template< int N, typename T >
MatrixLine<N, T>& MatrixLine<N, T>::operator=( const MatrixLine<N, T> & m ) {
    line = m.line;
    return *this;
}

template< int N, typename T >
MatrixLine<N, T>& MatrixLine<N, T>::operator=( const ConstMatrixLine<N, T>& m )
{
    line = m.line;
    return *this;
}

//Implementações de ConstMatrixLine

template< int N, typename T >
ConstMatrixLine<N, T>::ConstMatrixLine( std::array<T, N> const & line ):
    line( line )
{}

template< int N, typename T >
const T& ConstMatrixLine<N, T>::operator[]( size_t index ) const {
    return line[index];
}

template< int N, typename T >
ConstMatrixLine<N, T>::operator T() const {
    static_assert( N==1, "Conversão implícita disponível apenas para N == 1");
    return line[0];
}

} // namespace Math

#endif // MATRIX_LINE_H
