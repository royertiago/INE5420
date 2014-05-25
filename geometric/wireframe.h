/* wireframe.h
 * Objeto geométrico que representa uma estrutura N-dimensional,
 * via um modelo de arame.
 */
#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <vector>
#include <utility> //std::pair
#include "geometric/transformableObject.h"
#include "math/vector.h"
#include "render/renderer.h"

template< int N >
class Wireframe : public TransformableObject<N> {
    std::vector<Math::Vector<N>> vertices;
    std::vector<std::pair<int, int>> edges;
    /* Arestas são pares de inteiros, os índices
     * para as extremidades da aresta. */

public:
    Wireframe( std::vector<Math::Vector<N>> vertices,
               std::vector<std::pair<int, int>> edges );

    // Métodos herdados
    virtual void draw( Renderer<N>* ) override;
    virtual void transform( const Math::AffineOperator<N>& ) override;
    virtual Math::Vector<N> center() const override;
};

// Implementação
template< int N >
Wireframe<N>::Wireframe( std::vector<Math::Vector<N>> vertices,
                         std::vector<std::pair<int, int>> edges ) :
    vertices( vertices ),
    edges( edges )
{}

template< int N >
Math::Vector<N> Wireframe<N>::center() const {
    Math::Vector<N> c = vertices[0];
    for( int i = 1; i < vertices.size(); ++i )
        c = c + vertices[i];

    return c / vertices.size();
}

template< int N >
void Wireframe<N>::transform( const Math::AffineOperator<N>& op ) {
    for( int i = 0; i < vertices.size(); ++i )
        vertices[i] = op( vertices[i] );
}

template< int N >
void Wireframe<N>::draw( Renderer<N> * renderer ) {
    for( auto pair : edges )
        renderer->drawLine( vertices[pair.first], vertices[pair.second] );
}
#endif // WIREFRAME_H
