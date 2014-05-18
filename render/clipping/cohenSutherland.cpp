/* cohenSutherland.cpp
 * Implementação de cohenSutherland.h
 */

#include <cmath>
using std::fabs;
using std::fmin;
using std::fmax;
#include "cohenSutherland.h"


// Declaração de funções auxiliares
namespace {
    
    /* Tolerância usada para o clipping de retas alinhadas aos eixos. */
    const double epsilon = 1e-10;

    /* Códigos da região em que se encontra o ponto, em relação
     * à área de clipping (o quadrado [-1, 1] x [-1, 1]).
     *             |        |
     *  LEFT_TOP   |  TOP   | RIGHT_TOP
     * ------------+--------+-------------
     *             |        |
     *        LEFT | MIDDLE | RIGHT
     *             |        |
     * ------------+--------+-------------
     * LEFT_BOTTOM | BOTTOM | RIGHT_BOTTOM
     *             |        |
     * O quadrado central é o quadrado [-1, 1] x [-1, 1]. Um ponto
     * que esteja dentro deste quadrado possuirá código MIDDLE.
     *
     * Os códigos das regiões é definido de forma que seja possível
     * fazer operações bit-a-bit com eles e obter resultados corretos.
     * Por exemplo, LEFT | TOP == TOP_LEFT, e
     *  unsigned char code = regionOf( v );
     *  if( code & TOP )
     * testa se v está acima do quadrado; isto é, y > 1.
     */
    enum {
        MIDDLE       = 0x00,
        LEFT         = 0x01,
        RIGHT        = 0x02,
        TOP          = 0x10,
        BOTTOM       = 0x20,
        TOP_LEFT     = 0x11,
        TOP_RIGHT    = 0x12,
        BOTTOM_LEFT  = 0x21,
        BOTTOM_RIGHT = 0x22
    };
    
    /* Retorna a região do ponto passado. */
    unsigned char regionOf( ProjectedPoint& p ) {
        unsigned char code = MIDDLE;
        if( p.x < -1 )
            code |= LEFT;
        if( p.x > 1 )
            code |= RIGHT;

        if( p.y < -1 )
            code |= BOTTOM;
        if( p.y > 1 )
            code |= TOP;

        return code;
    }

    /* Efetua clipping no ponto passado, para que se enquadre
     * no quadrado [-1, 1] x [-1, 1].
     *
     * c é o coeficiente angular. Esta função modificará o ponto
     * passado para que fique na extremidade mais próxima da área
     * de clipping, mas ainda dentro de sua reta.
     *
     * Caso não haja interseção entre a reta e a área de clipping,
     * false é retornado; caso contrário, a função retorna true. */
    bool clip( ProjectedPoint& p, double c ) {
        unsigned char code = regionOf( p );
        /* A função que define a reta é
         *  y = r(x) = c * (x - p.x) + p.y
         * de forma que
         *  r(p.x) = p.y */
        double b = p.y, d = p.x;
        auto r = 
            [b, c, d](double x) -> double {
                return c * (x - d) + b;
            };

        if( code & LEFT ) {
            p.x = -1;
            p.y = r(-1);
        }
        else if( code & RIGHT ) {
            p.x = 1;
            p.y = r(1);
        }

        /* Neste momento, o ponto foi deslocado para
         * dentro da região delimitada pelas retas verticais
         * passando por (-1, 0) e (1, 0); isto é,
         * o ponto está em MIDDLE, TOP ou BOTTOM. 
         *
         * Se ele está em MIDDLE, podemos retornar: */
        code = regionOf( p );
        if( code == MIDDLE )
            return true;

        /* Caso contrário, temos de fazer mais um pouco de conta.
         *
         * Vamos agora olhar "de lado": escreveremos x = s(y):
         *  x = s(y) = (y - p.y) / c + p.x
         * de forma que
         *  s(p.y) = p.x */
        auto s =
            [b, c, d](double y) -> double {
                return (y - b)/c + d;
            };

        if( code & TOP ) {
            p.y = 1;
            p.x = s(1);
        }
        else if( code & BOTTOM ) {
            p.y = -1;
            p.x = s(-1);
        }

        /* Pode ser que, ainda assim, o ponto não esteja em MIDDLE;
         * neste caso, a reta não intersecta a área de clipping. */
        code = regionOf( p );
        return code == MIDDLE;
    }

    /* Algoritmo de clipping de Cohen-Sutherland */
    bool clip( ProjectedPoint& o, ProjectedPoint& d ) {
        unsigned char co = regionOf( o ); // region [c]ode of [o]rigin
        unsigned char cd = regionOf( d ); // region [c]ode of [d]estiny

        if( co == MIDDLE && cd == MIDDLE )
            return true;

        if( co & cd )
            /* Region codes: se o E lógico entre dois region codes
             * for não-zero, significa que o ponto está totalmente
             * fora da área de desenho. Não-zero == true. */
            return false;

        /* Evitar problemas com divisões por zero: caso a linha
         * seja quase vertical ou quase horizontal, podemos recortar
         * "no braço": */
        if( fabs( o.x - d.x ) < epsilon ) { //Vertical
            o.y = fmax( o.y, -1 );
            o.y = fmin( o.y, 1 );
            /* Isto garante que o.y é ao menos -1 e, no máximo, 1.
             * Isto é, o ponto 'o' acaba de ser jogado para dentro
             * do quadrado [-1, 1] x [-1, 1]. Façamos agora com 'd': */
            d.y = fmax( d.y, -1 );
            d.y = fmin( d.y, 1 );
            return true;
        }
        if( fabs( o.y - d.y ) < epsilon ) { //Horizontal
            o.x = fmax( o.x, -1 );
            o.x = fmin( o.x, 1 );
            d.x = fmax( d.x, -1 );
            d.x = fmin( d.x, 1 );
            return true;
        }

        double c = (o.y - d.y)/(o.x - d.x); //Coeficiente angular

        if( !clip( o, c ) )
            /* Se o ponto de origem ficou fora, a reta não intersecta
             * a área de clipping: */
            return false;

        //Agora, é só aparar o ponto de destino:
        return clip( d, c );
    }

} // anonymous namespace 

// Função no namsepace global
bool CohenSutherland( ProjectedPoint& o, ProjectedPoint& d ) {
    return clip( o, d );
}
