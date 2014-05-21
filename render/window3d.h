/* window3d.h
 * Especialização da estrutura de window.h para três dimensões.
 */
#ifndef WINDOW_3D_H
#define WINDOW_3D_H

#include "window.h"

#include "math/point.h"
#include "math/vector.h"
#include "math/linearOperator.h"

template<>
class Window<3> {
    Math::Point<3> center;
    double w, h; // Largura e altura da área de projeção (view plane)
    double d; // Distância da àrea de projeção
    Math::Vector<3> front;
    Math::Vector<3> viewUp;
    /* front é um vetor que aponta "para frente"; é o VPN (view plane normal)
     * com "sinal trocado". Já o viewUp é ortogonal a front e indica
     * onde fica "para cima", do ponto de vista de alguém que esteja
     * em center e olhando para front. */

    /* Operador linear que faz o mapeamento
     * coordenadas do mundo => coordenadas de window */
    mutable Math::LinearOperator<3> op;
    mutable bool cached; // Se op já foi calculado.

public:

    /* Constroi a window centrada no ponto {2, 2, 3}, apontando
     * para a origem do mundo, com d = 1, w = h = 2 e viewUp apontando
     * "para cima". */
    Window<3>();


    /* Altera o centro da window para o ponto passado. */
    void setCenter( Math::Point<3> p );

    /* Altera as dimensões da área de projeção. */
    void setWidth( double );
    void setHeight( double );
    void setDistance( double );

    /* Altera os vetores de visualização da window.
     * front e up serão assumidos ortogonais. */
    void setFront( Math::Vector<3> front );
    void setUp( Math::Vector<3> up );


    /* Movimenta a window no sentido desejado.
     *
     * Note que a movimentação será a mesma, independente da
     * orientação da window. */
    void move( Math::Vector<3> v );

    /* Movimenta a window para frente, a quantidade desejada.
     * Aceita valores negativos. */
    void moveFront( double );

    /* vertical scale: Multiplica a altura da área de projeção. */
    void vscale( double factor );

    /* horizontal scale: Multiplica a largura da área de projeção. */
    void hscale( double factor );

    /* Transforma tanto o vetor front quanto viewUp.
     * O operador linear deve ser ortogonal; isto é, não deve quebrar
     * a ortogonalidade entre front e viewUp. */
    void rotate( const Math::LinearOperator<3>& );


    // Métodos padrão
    double area() const;
    Math::Point<3> map( Math::Point<3> ) const;

private:
    /* Método auxiliar, que calcula o valor da transformação linear op */
    void computeTransform() const;
};

#endif // WINDOW_3D_H
