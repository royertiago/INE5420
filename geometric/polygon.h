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
#include "transformableObject.h"
#include "math/linearOperator.h"
#include "math/point.h"

template< int N >
class Polygon : public TransformableObject<N> {
    std::vector<Math::Point<N>> vertices;

public:
    /* Constrói o polígono com este vetor de pontos.
     * As arestas são constituídas de pontos adjacentes; o último
     * ponto é considerado ser adjacente do primeiro. */
    Polygon( std::vector<Math::Point<N>> );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual void transform( const Math::LinearOperator<N>& ) override;
    virtual Math::Point<N> center() const override;
};


//Implementação
template< int N >
Polygon<N>::Polygon( std::vector<Math::Point<N>> vertices ) :
    vertices( vertices )
{}

template< int N >
Math::Point<N> Polygon<N>::center() const {
    Math::Point<N> c = vertices[0];
    for( int i = 1; i < vertices.size(); ++i )
        c = c + vertices[i]; //TODO: implementar operadores adicionais


    for( int j = 0; j < N; ++j )
        c[j] /= vertices.size();
    return c;
}

template< int N >
void Polygon<N>::transform( const Math::LinearOperator<N>& op ) {
    for( int i = 0; i < vertices.size(); ++i )
        vertices[i] = op( vertices[i] );
}

template< int N >
void Polygon<N>::draw( Renderer<N> * renderer ) {
    for( int i = 0; i < vertices.size(); ++i )
        renderer->drawLine( vertices[i], vertices[(i+1) % vertices.size()] );
    /* Ligar os vértices vertices[i] e vertices[(i+1) % vertexCount]
     * tem dois efeitos interessantes: ao chegar no último vértice, o
     * renderizador ligará o último ponto com o primeiro (pois
     * vertexCount % vertexCount == 0) e, no caso patológico de o
     * polígono ter apenas um vértice, o renderizador ligará o ponto
     * nele mesmo - enchendo um pixel. */
}

#endif // POLYGON_H
