/* weilerAtherton.cpp
 * Implementação de weilerAtherton.h
 */
 
#include "weilerAtherton.h"

#include "render/clipping/clippingArea.h"

#include <vector>  // std::vector

#include "geometric/polygon.h"
#include "geometric/geometricFactory.h"

WeilerAtherton::WeilerAtherton( ClippingArea a ):
    ca(a)
{}

void WeilerAtherton::setArea( ClippingArea a) {
    ca = a;
}

std::vector<Polygon> WeilerAtherton::clip( Polygon& pol ) {

    std::vector<Polygon> afterClippingPolygons;
    afterClippingPolygons.push_back(pol);
    
    return afterClippingPolygons;
}
