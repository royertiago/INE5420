/* cohenSutherland.h
 * 
 * Algoritmo de clipping de linhas; implementa LineClipper.
 */
#ifndef COHEN_SUTHERLAND_H
#define COHEN_SUTHERLAND_H

#include "render/clipping/lineClipper.h"
#include "render/clipping/clippingArea.h"
#include "math/point.h"

class CohenSutherland : public LineClipper<2> {
private:
    ClippingArea ca;

public:
    /* Cria e vincula à área de clipping 'a' */
    CohenSutherland( ClippingArea a );

    virtual void setArea( ClippingArea ) override;
    virtual bool clip( Math::Point<2>&, Math::Point<2>& ) override;

    virtual ~CohenSutherland() = default;
    
private:
    /* Códigos da região em que se encontra o ponto, em relação
     * à área de clipping.
     *             |        |
     *  LEFT_TOP   |  TOP   | RIGHT_TOP
     * ------------+--------+-------------
     *             |        |
     *        LEFT | MIDDLE | RIGHT
     *             |        |
     * ------------+--------+-------------
     * LEFT_BOTTOM | BOTTOM | RIGHT_BOTTOM
     *             |        |
     * O quadrado central é delimitado pela área de clipping,
     * de forma que um ponto que esteja dentro da área de clipping
     * possuirá código MIDDLE.
     *
     * Os códigos das regiões é definido de forma que seja possível
     * fazer operações bit-a-bit com eles e obter resultados corretos.
     * Por exemplo, LEFT | TOP == TOP_LEFT, e
     *  unsigned char code = regionOf( v );
     *  if( code & TOP )
     * testa se v está no topo da área de clipping.
     */
    enum {
        MIDDLE       = 0x00,
        LEFT         = 0x01,
        RIGHT        = 0x02,
        TOP          = 0x10,
        BOTTOM       = 0x20,
        TOP_LEFT     = 0x11,
        TOP_RIGHT    = 0x12,
        BOTTOM_LEFT  = 0x21,
        BOTTOM_RIGHT = 0x22
    };
    
    /* Retorna a região do ponto passado. */
    unsigned char regionOf( Math::Point<2>& );

    /* Efetua clipping no ponto passado, para que se enquadre na
     * área de clipping.
     *
     * c é o coeficiente angular. Esta função modificará o ponto
     * passado para que fique na extremidade mais próxima da área
     * de clipping, mas ainda dentro de sua reta.
     *
     * Caso não haja interseção entre a reta e a área de clipping,
     * false é retornado; caso contrário, o método retorna true. */
    bool clip( Math::Point<2>&, double c );
};

#endif // COHEN_SUTHERLAND_H
