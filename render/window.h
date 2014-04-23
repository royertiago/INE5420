/* window.h
 * Tipo POD que representará a window ("virtual").
 *
 * A window é um objeto em coordenadas do mundo. Ela não possui
 * semântica - assim como a viewport - e depende da windowTransform
 * para mapear pontos do mundo para pontos numa área de clipping.
 */
#ifndef WINDOW_H
#define WINDOW_H

#include "math/vector.h"
#include "render/clipping/clippingArea.h"

struct Window {
    double x, y; // Coordenadas do centro da window
    double w, h; // Largura e altura da window
    double t; // Ângulo (theta) do view-up vector, em radianos.

    /* Constrói uma window cujos valores iniciais corresponderão
     * aos valores da área de clipping.
     *
     * O view-up vector estará alinhado com o eixo y. */
    Window( const ClippingArea& );

    /* Movimenta a window no sentido desejado.
     *
     * Note que a movimentação será a mesma, independente da
     * orientação da window - isto é, a movimentação é independente
     * do ângulo. Caso o ângulo seja importante, use Window::moveUp. */
    void move( Math::Vector<2> v );

    /* Movimenta a window no sentido desejado, tendo como referência
     * o ângulo da window.
     *
     * moveUp nem sempre move a window para cima; por exemplo, se o
     * ângulo do view-up vector for Pi/2, uma chamada como
     *  window.moveUp({ 0, -2 });
     * moverá a window 2 unidades para a direita, do ponto de vista
     * do mundo. */
    void moveUp( Math::Vector<2> v );

    /* vertical scale: Multiplica a altura da window pelo fator
     * desejado sem alterar seu centro. */
    void vscale( double factor );

    /* horizontal scale: Multiplica a largura da window pelo
     * fator desejado sem alterar seu centro. */
    void hscale( double factor );

    /* Rotaciona a window no sentido desejado.
     * angle está em radianos; ângulo positivo significa rotação
     * em sentido anti-horário. */
    void rotate( double angle );

    /* Informa a área da window. */
    double area() const;
};

//Implementações das funções mais simples

inline void Window::move( Math::Vector<2> v ) {
    x += v[0];
    y += v[1];
}

inline void Window::vscale( double factor ) {
    h *= factor;
}

inline void Window::hscale( double factor ) {
    w *= factor;
}
/* Cuidado com a nomenclatura: apesar do nome hscale, quem
 * mexe na variável h é vscale. */

inline void Window::rotate( double angle ) {
    t += angle;
}

inline double Window::area() const {
    return w * h;
}
#endif // WINDOW_H
