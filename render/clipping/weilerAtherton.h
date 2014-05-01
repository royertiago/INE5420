/* weilerAtherton.h
 * 
 * Algoritmo de clipping de polígonos; implementa polygonClipper.
 */
 
#ifndef WEILER_ATHERTON_H
#define WEILER_ATHERTON_H

#include "render/clipping/polygonClipper.h"
#include "render/clipping/clippingArea.h"
#include "math/point.h"

class WeilerAtherton : public PolygonClipper<2> {
private:
    ClippingArea ca;
    
public:
    /* Cria e vincula à área de clipping 'a' */
    WeilerAtherton( ClippingArea a);
    
    virtual void setArea( ClippingArea ) override;
    virtual bool clip( Math::Point<2> * v, int vertexCount ) override;
};

#endif // WEILER_ATHERTON_H
