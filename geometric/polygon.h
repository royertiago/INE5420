/* polygon.h
 * Objeto geométrico que representa um polígono vazado.
 *
 * O polígono fechar-se-á sozinho; isto é, para representar um triângulo,
 * bastam 3 pontos, não é necesário repetir o primeiro ponto.
 */
#ifndef POLYGON_H
#define POLYGON_H

#include <algorithm>
#include "render/renderer.h"
#include "transformableObject.h"
#include "math/linearOperator.h"
#include "math/point.h"

template< int N >
class Polygon : public TransformableObject<N> {
    Math::Point<N> * vertices;
    int vertexCount;

public:
    /* Constrói o polígono com este vetor de pontos, com a quantidade
     * referida de pontos.
     *
     * O polígono assumirá propriedade deste vetor de pontos e deletar-
     * -los-á junto consigo. */
    Polygon( Math::Point<N> * vertices, int vertexCount );

    /* Copia o conteúdo do poligono passado para este. */
    Polygon( const Polygon& );

    /* Transfere o conteúdo do polígono passado para este, deixando
     * o polígono passado como se tivesse sido construído com
     * o construtor padrão. */
    Polygon( Polygon&& );

    /* Copia o conteúdo do polígono passado para este. */
    Polygon& operator=( const Polygon& );

    /* Troca o conteúdo destes dois polígonos. */
    Polygon& operator=( Polygon&& );
    
    /* O destrutor deletará o vetor que lhe foi passado no construtor. */
    ~Polygon();


    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual void transform( const Math::LinearOperator<N>& ) override;
    virtual Math::Point<N> center() const override;
};


//Implementação
template< int N >
Polygon<N>::Polygon( Math::Point<N> * vertices, int vertexCount ) :
    vertices( vertices ),
    vertexCount( vertexCount )
{}

template< int N >
Polygon<N>::Polygon( const Polygon<N>& p ) :
    vertices( new Math::Point<N>[p.vertexCount] ),
    vertexCount( p.vertexCount )
{
    for( int i = 0; i < vertexCount; i++ )
        vertices[i] = p.vertices[i];
}

template< int N >
Polygon<N>::Polygon( Polygon<N>&& p ) :
    vertices( p.vertices ),
    vertexCount( p.vertexCount )
{
    p.vertices = nullptr;
    p.vertexCount = 0;
}

template< int N >
Polygon<N>& Polygon<N>::operator=( const Polygon<N>& p ) {
    delete vertices;
    vertices = new Math::Point<N>[p.vertexCount];
    vertexCount = p.vertexCount;
    std::copy( p.vertices, p.vertices + vertexCount, vertices );
    return *this;
}

template< int N >
Polygon<N>& Polygon<N>::operator=( Polygon<N>&& p ) {
    std::swap( vertices, p.vertices );
    std::swap( vertexCount, p.vertexCount );
    return *this;
}

template< int N >
Polygon<N>::~Polygon() {
    delete[] vertices;
}

template< int N >
Math::Point<N> Polygon<N>::center() const {
    Math::Point<N> c = vertices[0];
    for( int i = 1; i < vertexCount; ++i ) {
        for( int j = 0; j < N; ++j )
            c[j] = c[j] + vertices[i][j];
    }

    for( int j = 0; j < N; ++j )
        c[j] /= vertexCount;
    return c;
}

template< int N >
void Polygon<N>::transform( const Math::LinearOperator<N>& op ) {
    for( int i = 0; i < vertexCount; ++i )
        vertices[i] = op( vertices[i] );
}

template< int N >
void Polygon<N>::draw( Renderer<N> * renderer ) {
    for( int i = 0; i < vertexCount; i++ )
        renderer->drawLine( vertices[i], vertices[(i+1) % vertexCount] );
    /* Ligar os vértices vertices[i] e vertices[(i+1) % vertexCount]
     * tem dois efeitos interessantes: ao chegar no último vértice, o
     * renderizador ligará o último ponto com o primeiro (pois
     * vertexCount % vertexCount == 0) e, no caso patológico de o
     * polígono ter apenas um vértice, o renderizador ligará o ponto
     * nele mesmo - enchendo um pixel. */
}

#endif // POLYGON_H
