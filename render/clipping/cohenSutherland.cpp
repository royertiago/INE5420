/* cohenSutherland.cpp
 * Implementação de cohenSutherland.h
 */

#include "cohenSutherland.h"

CohenSutherland::CohenSutherland( ClippingArea a ): 
    clippingArea(a)
{}

void CohenSutherland::setArea( ClippingArea a ) {
    clippingArea = a;
}


bool CohenSutherland::clip( Math::Point<2>& p1, Math::Point<2>& p2 )
{
    if(isInsideMyClippingArea(p1) && isInsideMyClippingArea(p2))
        return true;
    else
    {
        return false;
    }
}

bool CohenSutherland::isInsideMyClippingArea( Math::Point<2>& p )
{
    bool xInside = p[0] >= clippingArea.xmin && p[0] <= clippingArea.xmax;
    bool yInside = p[1] >= clippingArea.ymin && p[1] <= clippingArea.ymax;
    return (xInside && yInside);
}
