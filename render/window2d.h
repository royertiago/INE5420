/* window2d.h
 * Especialização da estrutura de window.h para duas dimensões.
 */
#ifndef WINDOW_2D_H
#define WINDOW_2D_H

#include "render/window.h"

#include "math/point.h"
#include "math/vector.h"
#include "math/linearOperator.h"
#include "test/lib/declarationMacros.h"

template<>
class Window<2> {
    double x, y; // Coordenadas do centro da window
    double w, h; // Largura e altura da window
    double t; // Ângulo (theta) do view-up vector, em radianos.

    /* Operador linear que faz o mapeamento
     * coordenadas do mundo => coordenadas de window */
    mutable Math::LinearOperator<2> op;
    mutable bool cached; // Se op já foi calculado.

    TEST_FRIEND( Window2DTest );
public:

    /* Constroi a window centrada na origem apontada para cima
     * com largura e altura 2. */
    Window<2>();


    /* Altera o centro da window para o ponto passado. */
    void setCenter( Math::Point<2> p );

    /* Altera as dimensões da window. */
    void setWidth( double );
    void setHeight( double );

    /* Altera o ângulo do view-up vector. */
    void setTheta( double );


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


    // Métodos padrão
    double area() const;
    Math::Point<2> map( Math::Point<2> ) const;

private:
    /* Método auxiliar, que calcula o valor da transformação linear op */
    void computeTransform() const;
};

#endif // WINDOW_2D_H
