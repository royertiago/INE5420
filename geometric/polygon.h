/* polygon.h
 * Objeto geométrico que representa um polígono vazado.
 *
 * O polígono fechar-se-á sozinho; isto é, para representar um triângulo,
 * basatm 3 pontos, não é necesário repetir o primeiro ponto.
 */
#ifndef POLYGON_H
#define POLYGON_H

#include "geometricObject.h"
#include "point.h"

class Renderer;

class Polygon : public GeometricObject {
    Point<2> * vertices;
    int vertexCount;

public:
    /* Constrói o polígono com este vetor de pontos, com a quantidade
     * referida de pontos.
     *
     * O polígono assumirá propriedade deste vetor de pontos e deletar-
     * -los-á junto consigo. */
    Polygon( Point<2> * vertices, int vertexCount ) :
        vertices( vertices ),
        vertexCount( vertexCount )
    {}

    /* Constrói o polígono com os pontos desejados, na ordem desejada.
     *
     * Tenha certeza de que os tipos passados são convertíves para Point<2>;
     * o compilador pode ser um pouco grosso caso isso não ocorra. */
    template< typename ... Types >
    Polygon( Types... ts ) :
        vertices( new Point<2>[sizeof...(Types)] { ts... } ),
        vertexCount( sizeof...(Types) )
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

    /* O destrutor deletará o vetor que lhe foi passado no construtor. */
    ~Polygon();

    virtual void draw( Renderer * ) override;
};

#endif // POLYGON_H
