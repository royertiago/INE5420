/* cubicSpline.h
 * Classe que representa uma spline cúbica genérica.
 * Veja em SplineFactory.h funções que geram curvas cúbicas
 * de Hermite e Bézier e B-splines. */
#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

#include "math/polynomial.h"
#include "math/vector.h"
#include "math/point.h"
#include "geometric/transformableObject.h"
#include "render/renderer.h"

template< int N >
class CubicSpline : public TransformableObject<N> {
    Math::Polynomial< Math::Vector<N> > p;
    Math::Point<N> c; // center

public:
    /* Constrói uma spline cúbica com os referidos coeficientes.
     * Este objeto assumirá controle sobre o ponteiro passado,
     * que deve conter exatamente quatro elementos. */
    CubicSpline( Math::Vector<N>* coefficients, Math::Point<N> center );

    // Métodos herdados
    virtual void draw( Renderer * ) override;
    virtual void transform( const Math::LinearOperator<N>& ) override;
    virtual Math::Point<N> center() const override;
};

// Implementações
template< int N >
CubicSpline<N>::CubicSpline( Math::Vector<N>* pc, Math::Point<N> center ) :
    p( pc, 3 ),
    c( center )
{}

template< int N >
void CubicSpline<N>::draw( Renderer * renderer ) {
    double sqnorm = (p(0) - p(1)).sqnorm();
    int pixels = sqnorm * renderer->density();
    /* Assumiremos que a derivada do polinômio nunca fica
     * significativamente maior do que a diferença entre
     * os pontos inicial e final da spline.
     *
     * Podemos imaginar, portanto, que ocuparemos sqnorm * density()
     * pixels na tela. Vamos tentar desenhar retas entre cada
     * quadrado de dez pixels: */
    double delta = 100.0/pixels;
    for( double t = 0; t < 1; t += delta )
        renderer->drawLine( p(t), p(t + delta) );
}

template< int N >
void CubicSpline<N>::transform( const Math::LinearOperator<N>& op ) {
    c = op( c );
    for( int i = 0; i < 3; ++i )
        p[i] = Math::Vector<N>(op( Math::Point<N>(p[i]) ));
}

template< int N >
Math::Point<N> CubicSpline<N>::center() const {
    return c;
}

#endif // CUBIC_SPLINE_H
