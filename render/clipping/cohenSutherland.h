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
    ClippingArea clippingArea;

public:
    /* Construtores */
    /* Cria e vincula à área de clipping 'a' */
    CohenSutherland( ClippingArea a );

    virtual void setArea( ClippingArea ) override;
    virtual bool clip( Math::Point<2>&, Math::Point<2>& ) override;

    virtual ~CohenSutherland() = default;
    
private:
    /* Funções privadas que auxiliam o clipping */
    enum Region { TOP_LEFT, TOP, TOP_RIGHT,
                  MIDDLE_LEFT, MIDDLE, MIDDLE_RIGHT,
                  BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT };
    
    // Retorna uma das constantes definidas no enum Region
    int regionOf( Math::Point<2>& );
};

#endif // COHEN_SUTHERLAND_H
