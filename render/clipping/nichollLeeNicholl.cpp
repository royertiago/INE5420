/* nichollLeeNicholl.cpp */

#include "nichollLeeNicholl.h"

NichollLeeNicholl::NichollLeeNicholl( ClippingArea a ) : clippingArea(a)
{}

void NichollLeeNicholl::setArea( ClippingArea a )
{ clippingArea = a; }


bool NichollLeeNicholl::clip( Math::Point<2>& p1, Math::Point<2>& p2 )
{
    if(isInsideMyClippingArea(p1) && isInsideMyClippingArea(p2))
        return true;
    else
    {
        return false;
    }
}

bool NichollLeeNicholl::isInsideMyClippingArea( Math::Point<2>& p )
{
    bool xInside = p[0] >= clippingArea.xmin && p[0] <= clippingArea.xmax;
    bool yInside = p[1] >= clippingArea.ymin && p[1] <= clippingArea.ymax;
    return (xInside && yInside);
}
