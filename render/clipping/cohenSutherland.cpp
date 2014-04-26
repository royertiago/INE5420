/* cohenSutherland.cpp
 * Implementação de cohenSutherland.h
 */

#include <cmath>
using std::fabs;
using std::fmin;
using std::fmax;

#include "cohenSutherland.h"

CohenSutherland::CohenSutherland( ClippingArea a ): 
    ca(a)
{}

void CohenSutherland::setArea( ClippingArea a ) {
    ca = a;
}

static const double epsilon = 1e-10;

bool CohenSutherland::clip( Math::Point<2>& o, Math::Point<2>& d ) {
    unsigned char co = regionOf( o ); // region [c]ode of [o]rigin
    unsigned char cd = regionOf( d ); // region [c]ode of [d]estiny

    if( co == MIDDLE && cd == MIDDLE )
        return true;

    if( co & cd )
        /* Region codes: se o E lógico entre dois region codes
         * for não-zero, significa que o ponto está totalmente
         * fora da área de desenho. Não-zero ~= true. */
        return false;

    /* Evitar problemas com divisões por zero: caso a linha
     * seja quase vertical ou quase horizontal, podemos recortar
     * "no braço": */
    if( fabs( o[0] - d[0] ) < epsilon ) { //Vertical
        o[1] = fmax( o[1], ca.ymin );
        o[1] = fmin( o[1], ca.ymax );
        /* Isto garante que o[1] é ao menos ca.ymin e, no máximo,
         * ca.ymax. Façamos agora com d[1]: */
        d[1] = fmax( d[1], ca.ymin );
        d[1] = fmin( d[1], ca.ymax );
        return true;
    }
    if( fabs( o[1] - d[1] ) < epsilon ) { //Horizontal
        o[0] = fmax( o[0], ca.xmin );
        o[0] = fmin( o[0], ca.xmax );
        d[0] = fmax( d[0], ca.xmin );
        d[0] = fmin( d[0], ca.xmax );
        return true;
    }

    double c = (o[1] - d[1])/(o[0] - d[0]); //Coeficiente angular

    if( !clip( o, c ) )
        /* Se o ponto de origem ficou fora, a reta não intersecta
         * a área de clipping. */
        return false;

    //Agora, é só aparar o ponto de destino:
    return clip( d, c );
}


bool CohenSutherland::clip( Math::Point<2>& p, double c ) {
    unsigned char code = regionOf( p );
    /* A função que define a reta é
     *  y = r(x) = c * (x - p[0]) + p[1]
     * de forma que
     *  r(p[0]) = p[1] */
    double b = p[1], d = p[0];
    auto r = 
        [b, c, d](double x) -> double {
            return c * (x - d) + b;
        };

    if( code & LEFT ) {
        p[0] = ca.xmin;
        p[1] = r(ca.xmin);
    }
    else if( code & RIGHT ) {
        p[0] = ca.xmax;
        p[1] = r(ca.xmax);
    }

    /* Neste momento, o ponto foi deslocado para
     * dentro da região delimitada pelas retas verticais
     * passando por (ca.xmin, 0) e (ca.xmax, 0); isto é,
     * o ponto está em MIDDLE, TOP ou BOTTOM. 
     *
     * Se ele está em MIDDLE, podemos retornar: */
    code = regionOf( p );
    if( code == MIDDLE )
        return true;

    /* Caso contrário, temos de fazer mais um pouco de conta.
     *
     * Vamos agora olhar "de lado": escreveremos x = s(y):
     *  x = s(y) = (y - p[1]) / c + p[0]
     * de forma que
     *  s(p[1]) = p[0] */
    auto s =
        [b, c, d](double y) -> double {
            return (y - b)/c + d;
        };

    if( code & TOP ) {
        p[1] = ca.ymax;
        p[0] = s(ca.ymax);
    }
    else if( code & BOTTOM ) {
        p[1] = ca.ymin;
        p[0] = s(ca.ymax);
    }

    /* Pode ser que, ainda assim, o ponto não está em MIDDLE;
     * neste caso, a reta não intersecta a área de clipping. */
    code = regionOf( p );
    return code == MIDDLE;
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
