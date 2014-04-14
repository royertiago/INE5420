/* window.h
 * Tipo POD que representará a window ("virtual").
 *
 * Optou-se por guardar na window os valores xmin/ymin/xmax/ymax
 * ao invés de centro/altura/largura por eles serem necessários
 * mais frequentemente do que movimentações/zoom na window.
 */
#ifndef WINDOW_H
#define WINDOW_H

#include "math/vector.h"

struct Window {
    double xmin;
    double ymin;
    double xmax;
    double ymax;

    /* Movimenta a window no sentido desejado. */
    void move( double x, double y );
    void move( Math::Vector<2> v );

    /* vertical scale: Multiplica a altura da window pelo fator
     * desejado sem alterar seu centro. */
    void vscale( double factor );

    /* horizontal scale: Multiplica a largura da window pelo
     * fator desejado sem alterar seu centro. */
    void hscale( double factor );

    //TODO: scale(Vector<2>);
};

#endif // WINDOW_H
