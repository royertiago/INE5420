/* polygon.h
 * Objeto geométrico que representa um polígono vazado.
 *
 * O polígono fechar-se-á sozinho; isto é, para representar um triângulo,
 * basatm 3 pontos, não é necesário repetir o primeiro ponto.
 */
#ifndef POLYGON_H
#define POLYGON_H

#include "transformableObject.h"
#include "math/linearOperator.h"
#include "math/point.h"

class Renderer;

class Polygon : public TransformableObject<2> {
    Math::Point<2> * vertices;
    int vertexCount;

public:
    /* Constrói o polígono com este vetor de pontos, com a quantidade
     * referida de pontos.
     *
     * O polígono assumirá propriedade deste vetor de pontos e deletar-
     * -los-á junto consigo. */
    Polygon( Math::Point<2> * vertices, int vertexCount ) :
        vertices( vertices ),
        vertexCount( vertexCount )
    {}

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
    
    /* Retorna os vértices do polígono. */
    const Math::Point<2>* getVertices();
    
    /* Retorna o número de vértices do polígono. */
    const int getVertexCount();

    /* O destrutor deletará o vetor que lhe foi passado no construtor. */
    ~Polygon();


    // Métodos herdados
    virtual void draw( Renderer * ) override;
    virtual void transform( const Math::LinearOperator<2>& ) override;
    virtual Math::Point<2> center() const override;
};



//Implementação das funções mais simples 

inline Polygon::Polygon( Polygon&& p ) :
    vertices( p.vertices ),
    vertexCount( p.vertexCount )
{
    p.vertices = nullptr;
    p.vertexCount = 0;
}

inline const Math::Point<2>* Polygon::getVertices() {
    return vertices;
}

inline const int Polygon::getVertexCount() {
    return vertexCount;
}

inline Polygon::~Polygon() {
    delete vertices;
}

#endif // POLYGON_H
