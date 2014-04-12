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

#include "matrix.h"

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
        vector(N) = 1.0; //TODO: implementar vector[N];
    }

    /* Converte um vetor n-dimensional num ponto n-dimensional. */
    Point( const Math::Vector<N>& );

    Point( const Point& ) = default;
    Point( Point&& ) = default;
    Point& operator=( const Point& ) = default;
    Point& operator=( Point&& ) = default;
    ~Point() = default;

    double& operator[]( size_t index ) {
        return vector( index );
    }
};
