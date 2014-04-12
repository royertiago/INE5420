/* polygon.cpp
 * Implementação de polygon.h
 */

#include <algorithm>

#include "polygon.h"
#include "point.h"
#include "renderer.h"

Polygon::Polygon( const Polygon& p ) :
    vertices( new Point<2>[p.vertexCount] ),
    vertexCount( p.vertexCount )
{
    for( int i = 0; i < vertexCount; i++ )
        vertices[i] = p.vertices[i];
}

Polygon::Polygon( Polygon&& p ) :
    vertices( p.vertices ),
    vertexCount( p.vertexCount )
{
    p.vertices = nullptr;
    p.vertexCount = 0;
}

Polygon::~Polygon() {
    delete vertices;
}

Polygon& Polygon::operator=( const Polygon& p ) {
    delete vertices;
    vertices = new Point<2>[p.vertexCount];
    vertexCount = p.vertexCount;
    std::copy( p.vertices, p.vertices + vertexCount, vertices );
    return *this;
}

Polygon& Polygon::operator=( Polygon&& p ) {
    std::swap( vertices, p.vertices );
    std::swap( vertexCount, p.vertexCount );
    return *this;
}

void Polygon::draw( Renderer * renderer ) {
    for( int i = 0; i < vertexCount; i++ )
        renderer->drawLine( vertices[i], vertices[(i+1) % vertexCount] );
    /* Ligar os vértices vertices[i] e vertices[(i+1) % vertexCount]
     * tem dois efeitos interessantes: ao chegar no último vértice, o
     * renderizador ligará o último ponto com o primeiro (pois
     * vertexCount % vertexCount == 0) e, no caso patológico de o
     * polígono ter apenas um vértice, o renderizador ligará o ponto
     * nele mesmo - enchendo um pixel. */
}
