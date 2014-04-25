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
    if(regionOf(p1) == MIDDLE && regionOf(p2) == MIDDLE)
        return true;
    else
    {   
        return false;
    }
}

int CohenSutherland::regionOf( Math::Point<2>& p )
{
    if( p[0] < clippingArea.xmin ) // O ponto está à esquerda
    {
        if( p[1] > clippingArea.ymax )
            return TOP_LEFT;
        if( p[1] < clippingArea.ymin )
            return BOTTOM_LEFT;
        
        return MIDDLE_LEFT;
    }
    if( p[0] > clippingArea.xmax ) // O ponto está à direita
    {
        if( p[1] > clippingArea.ymax )
            return TOP_RIGHT;
        if( p[1] < clippingArea.ymin )
            return BOTTOM_RIGHT;
        
        return MIDDLE_RIGHT;
    }
    // O ponto está ao meio
        if( p[1] > clippingArea.ymax )
            return TOP;
        if( p[1] < clippingArea.ymin )
            return BOTTOM;
            
    return MIDDLE;
}
