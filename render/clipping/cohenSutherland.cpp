/* cohenSutherland.cpp
 * Implementação de cohenSutherland.h
 */

#include "cohenSutherland.h"

CohenSutherland::CohenSutherland( ClippingArea a ): 
    ca(a)
{}

void CohenSutherland::setArea( ClippingArea a ) {
    ca = a;
}


bool CohenSutherland::clip( Math::Point<2>& p1, Math::Point<2>& p2 )
{
    if(regionOf(p1) == MIDDLE && regionOf(p2) == MIDDLE)
        return true;
    else
    {   
        return false;
    }
}

unsigned char CohenSutherland::regionOf( Math::Point<2>& p ) {
    unsigned char code = MIDDLE;
    if( p[0] < ca.xmin )
        code |= LEFT;
    if( p[0] > ca.xmax )
        code |= RIGHT;

    if( p[1] < ca.ymin )
        code |= BOTTOM;
    if( p[1] > ca.ymax )
        code |= TOP;

    return code;
}
