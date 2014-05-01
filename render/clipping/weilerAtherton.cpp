/* weilerAtherton.cpp
 * Implementação de weilerAtherton.h
 */
 
#include "weilerAtherton.h"

WeilerAtherton::WeilerAtherton( ClippingArea a ):
    ca(a)
{}

void WeilerAtherton::setArea( ClippingArea a) {
    ca = a;
}

bool WeilerAtherton::clip(Math::Point<2> * v, int vertexCount) {
    return false;
}
