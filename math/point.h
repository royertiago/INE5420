/* point.h
 * Classe que representa um ponto.
 * 
 * Gambiarra para transformar translações numa transformação linear:
 * pontos n-dimensionais são vetores (n+1)-dimensionais cuja última
 * coordenada é sempre 1.
 *
 * Note que, embora objetos desta classe sejam inicializados com
 * vetores cuja última coordenada é 1, é responsabilidade do programador
 * garantir que esta invariante seja preservada.
 *
 * A modelagem adotada é que o ponto conterá o vetor de uma dimensão
 * a mais; dessa forma, podemos usar asserções para garantir que
 * o vetor "codifica" um ponto válido.
 */
#ifndef POINT_H
#define POINT_H

#include <initializer_list>

#include "math/vector.h"
#include "math/matrixLine.h"

namespace Math {

template <int N> class LinearOperator;

template <int N>
class Point {
    /* Vetor (n+1)-dimensional que representará este ponto.
     * Temos de garantir que vector[N] seja sempre 1. */
    Math::Vector< N+1 > vector;

public:
    /* Constrói um ponto.
     *
     * A única inicialização feita é da última coordenada: ela é
     * alterada para 1. As demais coordenadas não são inicializadas. */
    Point() {
        vector[N] = 1.0;
    }

    /* Converte um vetor n-dimensional num ponto n-dimensional. */
    explicit Point( const Math::Vector<N>& );

    /* Encapsula o vetor n+1-dimensional neste ponto.
     * Atenção: nenhuma checagem de valores é feita para garatir que a
     * última dimensão é válida. */
    Point( const Math::Vector<N+1>& v ) :
        vector(v)
    {}

    /* Listas de inicialização.
     * Inicializa todas as dimensões disponíveis para o valor correspondente
     * e o que restar para zero; dimensões extras serão ignoradas.
     * Note que a dimensão N está oculta, portanto, será ignorada. 
     *
     * Exemplo:
     *  Point<2> x{1.1, 2.2, 3.3};
     * O úlitmo double é ignorado.
     */
    Point( std::initializer_list<double> );

    Point( const Point<N>& ) = default;
    Point( Point<N>&& ) = default;
    Point<N>& operator=( const Point<N>& ) = default;
    Point<N>& operator=( Point<N>&& ) = default;
    ~Point() = default;

    Math::MatrixLine<1> operator[]( size_t index ) {
        return vector[ index ];
    }
    Math::ConstMatrixLine<1> operator[]( size_t index ) const {
        return vector[ index ];
    }

    friend class LinearOperator< N >;
};

template< int N >
Point<N>::Point( const Math::Vector<N>& source ) {
    for( int i = 0; i < N; i++ )
        vector[i] = source[i];
    vector(N) = 1.0;
}

template< int N >
Point<N>::Point( std::initializer_list<double> source ) {
    int i = 0;
    auto it = source.begin();
    for( ; i < N && it != source.end(); ++i, ++it )
        vector[i] = *it;
    for( ; i < N; ++i )
        vector[i] = 0;
    vector[N] = 1.0;
}

} // namespace Math
#endif // POINT_H
