/* polygon.h
 * Objeto geométrico que representa um polígono vazado.
 *
 * O polígono fechar-se-á sozinho; isto é, para representar um triângulo,
 * bastam 3 pontos, não é necesário repetir o primeiro ponto.
 */
#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "render/renderer.h"
#include "geometric/transformableObject.h"
#include "math/affineOperator.h"
#include "math/vector.h"

template< int N >
class Polygon : public TransformableObject<N> {
    std::vector<Math::Vector<N>> vertices;

public:
    /* Constrói o polígono com este vetor de pontos.
     * As arestas são constituídas de pontos adjacentes; o último
     * ponto é considerado ser adjacente do primeiro. */
    Polygon( std::vector<Math::Vector<N>> );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual void transform( const Math::AffineOperator<N>& ) override;
    virtual Math::Vector<N> center() const override;
};


//Implementação
template< int N >
Polygon<N>::Polygon( std::vector<Math::Vector<N>> vertices ) :
    vertices( vertices )
{}

template< int N >
Math::Vector<N> Polygon<N>::center() const {
    Math::Vector<N> c = vertices[0];
    for( unsigned i = 1; i < vertices.size(); ++i )
        c = c + vertices[i]; //TODO: implementar operadores adicionais

    return c / vertices.size();
}

template< int N >
void Polygon<N>::transform( const Math::AffineOperator<N>& op ) {
    for( unsigned i = 0; i < vertices.size(); ++i )
        vertices[i] = op( vertices[i] );
}

template< int N >
void Polygon<N>::draw( Renderer<N> * renderer ) {
    for( unsigned i = 0; i < vertices.size(); ++i )
        renderer->drawLine( vertices[i], vertices[(i+1) % vertices.size()] );
    /* Ligar os vértices vertices[i] e vertices[(i+1) % vertexCount]
     * tem dois efeitos interessantes: ao chegar no último vértice, o
     * renderizador ligará o último ponto com o primeiro (pois
     * vertexCount % vertexCount == 0) e, no caso patológico de o
     * polígono ter apenas um vértice, o renderizador ligará o ponto
     * nele mesmo - preenchendo um pixel. */
}

#endif // POLYGON_H
