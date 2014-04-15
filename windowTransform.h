/* windowTransform.h
 * Objeto capaz de fazer o mapeamento entre coordenadas do mundo 
 * para coordenadas da window. Este mapeamento é feito com base 
 * numa área de clipping, definida pelo próprio objeto.
 *
 * Objetos desta classe possuem um objeto Window dentro de si.
 * Para alterar este objeto, execute o método window(); este método
 * retornará uma referência para o objeto, que pode sofrer chamadas
 * como rotate(). O objeto assumirá que toda chamada ao método
 * window() irá mudar a window.
 *
 * A window foi encrustada dentro da WindowTransform pela necessidade
 * de alterar a função de transformação toda vez que a window fosse
 * alterada; então, deixamos que a windowTransform cuide deste recálculo.
 *
 * Embora a implementação atual utilize coordenadas normalizadas
 * nas coordenadas de window, pode não sê-lo nas implementações
 * futuras. Para referir-se a área de clipping mirada pela
 * transformação, utilize o método clippingArea().
 */
#ifndef WINDOW_TRANSFORM_H
#define WINDOW_TRANSFORM_H

#include "window.h"
#include "clippingArea.h"
#include "point.h"
#include "linearOperator.h"

class WindowTransform {
    mutable LinearOperator<2> lo;
    /* Clean será alterado para false toda vez que a window tiver
     * mudado de lugar. Isto significa que temos de recalcular
     * o valor de lo. */
    mutable bool cached;

    Window w;

    /* Calcula o operador linear lo, baseado na window atual.
     * Este método modifica o objeto lo. */
    void computeTransform() const;

public:

    /* Constrói uma transformação linear cuja janela inical será w. */
    WindowTransform( Window w );

    /* Retorna a window deste objeto. Esta chamada pode ser utilizada
     * para alterar a window desta transformada. */
    Window& window();
    const Window& window() const;

    /* Aplica a transformada de window no ponto passado. */
    Point<2> operator()( Point<2> ) const;

    /* Informa a área de clipping alvejada por esta transformada
     * de window.
     *
     * O valor de retorno é uma referência pois, caso a área de clipping
     * seja alterada internamente, esta alteracão se refletirá
     * automaticamente no objeto da função chamadora. */
    const ClippingArea& clippingArea() const;
};

//Implementação das funções mais simples

inline WindowTransform::WindowTransform( Window w ) :
    lo(),
    cached( false ),
    w( w )
{}

inline Window& WindowTransform::window() {
    cached = false;
    return w;
}

inline const Window& WindowTransform::window() const {
    return w;
}

inline Point<2> WindowTransform::operator()( Point<2> p ) const {
    if( !cached )
        computeTransform();
    return lo.transform( p );
}

/* Por simplicidade, por ora, usaremos apenas coordenadas normalizadas. */
inline const ClippingArea& WindowTransform::clippingArea() const {
    return ClippingArea::normalized;
}

#endif // WINDOW_TRANSFORM_H
