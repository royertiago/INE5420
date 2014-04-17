/* polygon.cpp
 * Implementação de polygon.h
 */

#include <algorithm>

#include "polygon.h"
#include "point.h"
#include "linearOperator.h"
#include "renderer.h"

Polygon::Polygon( const Polygon& p ) :
    vertices( new Point<2>[p.vertexCount] ),
    vertexCount( p.vertexCount )
{
    for( int i = 0; i < vertexCount; i++ )
        vertices[i] = p.vertices[i];
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

Point<2> Polygon::center() const {
   Point<2> c = vertices[0];
   for( int i = 1; i < vertexCount; ++i ) {
       c[0] = vertices[i][0];
       c[1] = vertices[i][1];
   }
   c[0] /= vertexCount;
   c[1] /= vertexCount;
   return c;
}

void Polygon::transform( const LinearOperator<2>& op ) {
    for( int i = 0; i < vertexCount; ++i )
        vertices[i] = op( vertices[i] );
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
