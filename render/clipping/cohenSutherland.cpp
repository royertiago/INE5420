/* cohenSutherland.cpp
 * Implementação de cohenSutherland.h
 */

#include <cmath>
using std::fabs;

#include "cohenSutherland.h"

const double epsilon = 1e-10;

CohenSutherland::CohenSutherland( ClippingArea a ): 
    clippingArea(a)
{}

void CohenSutherland::setArea( ClippingArea a ) {
    clippingArea = a;
}


bool CohenSutherland::clip( Math::Point<2>& p1, Math::Point<2>& p2 )
{
    int r1 = regionOf(p1);
    int r2 = regionOf(p2);
    if(r1 == MIDDLE && r2 == MIDDLE)
        // Caso trivial; nenhum clipping a ser feito.
        return true;

    if(r1 & r2)
        /* Region codes: se o E lógico entre dois region codes
         * for não-zero, significa que o ponto está totalmente
         * fora da área de desenho. Não-zero ~= true. */
        return false;

    /* Primeiro caso patológico: um ponto está acima do outro, 
     * formando uma reta vertical, não uma função afim. */
    if( fabs( p1[0] == p2[0] ) < epsilon ) {
        if( p1[0] < a.xmin || p1[0] > a.xmax ) // fora da área de clipping
            return false;
        p1[1] = fmax( p[1], a.ymax );
        p1[1] = fmin( p[1], a.ymin );
        p2[1] = fmax( p[1], a.ymax );
        p2[1] = fmin( p[1], a.ymin ); // Aparar por cima e por baixo
        return true;
    }

    double c = (p1[1] - p2[1])/(p1[0] - p2[0]); //Coeficiente angular
    return true;
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
