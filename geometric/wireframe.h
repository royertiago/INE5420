/* wireframe.h
 * Objeto geométrico que representa uma estrutura N-dimensional,
 * via um modelo de arame.
 */
#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <vector>
#include <utility> //std::pair
#include "geometric/transformableObject.h"
#include "math/point.h"
#include "render/renderer.h"

template< int N >
class Wireframe : public TransformableObject<N> {
    std::vector<Math::Point<N>> vertices;
    std::vector<std::pair<int, int>> edges;
    /* Arestas são pares de inteiros, os índices
     * para as extremidades da aresta. */

public:
    Wireframe( std::vector<Math::Point<N>> vertices,
               std::vector<std::pair<int, int>> edges );

    // Métodos herdados
    virtual void draw( Renderer<N>* ) override;
    virtual void transform( const Math::LinearOperator<N>& ) override;
    virtual Math::Point<N> center() const override;
};

// Implementação
template< int N >
Wireframe<N>::Wireframe( std::vector<Math::Point<N>> vertices,
                         std::vector<std::pair<int, int>> edges ) :
    vertices( vertices ),
    edges( edges )
{}

template< int N >
Math::Point<N> Wireframe<N>::center() const {
    Math::Point<N> c = vertices[0];
    for( int i = 1; i < vertices.size(); ++i )
        c = c + vertices[i];

    for( int j = 0; j < N; ++j )
        c[j] /= vertices.size(); //TODO: remover código duplicado
    return c;
}

template< int N >
void Wireframe<N>::transform( const Math::LinearOperator<N>& op ) {
    for( int i = 0; i < vertices.size(); ++i )
        vertices[i] = op( vertices[i] );
}

template< int N >
void Wireframe<N>::draw( Renderer<N> * renderer ) {
    for( auto pair : edges )
        renderer->drawLine( vertices[pair.first], vertices[pair.second] );
}
#endif // WIREFRAME_H
