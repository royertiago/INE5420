/* cubicSpline.h
 * Classe que representa uma spline cúbica genérica.
 * Veja em SplineFactory.h funções que geram curvas cúbicas
 * de Hermite e Bézier e B-splines. */
#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

#include "math/polynomial.h"
#include "math/vector.h"
#include "geometric/transformableObject.h"
#include "render/renderer.h"

template< int N >
class CubicSpline : public TransformableObject<N> {
    Math::Polynomial< Math::Vector<N> > p;
    Math::Vector<N> c; // center

public:
    /* Constrói uma spline cúbica com os referidos coeficientes. */
    CubicSpline( std::vector<Math::Vector<N>> coefficients, 
            Math::Vector<N> center );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual void transform( const Math::AffineOperator<N>& ) override;
    virtual Math::Vector<N> center() const override;
};

// Implementações
template< int N >
CubicSpline<N>::CubicSpline( std::vector<Math::Vector<N>> pc,
        Math::Vector<N> center ) :
    p( pc ),
    c( center )
{}

template< int N >
void CubicSpline<N>::draw( Renderer<N> * renderer ) {
    int pixels = norm(p(0) - p(1)) * renderer->density();
    /* Assumiremos que a derivada do polinômio nunca fica
     * significativamente maior do que a diferença entre
     * os pontos inicial e final da spline.
     *
     * Podemos imaginar, portanto, que ocuparemos norm * density()
     * pixels na tela. Vamos tentar desenhar retas entre cada
     * quadrado de dez pixels: */
    double delta = 100.0/pixels;
    auto it = p.iterator( 0, delta );
    Math::Vector<N> current = *it;
    ++it;
    Math::Vector<N> next = *it;
    for( ; it < 1; ++it, current = next, next = *it )
        renderer->drawLine( current, next );
}

template< int N >
void CubicSpline<N>::transform( const Math::AffineOperator<N>& op ) {
    c = op( c );
    for( int i = 0; i < 3; ++i )
        p[i] = op( p[i] );
}

template< int N >
Math::Vector<N> CubicSpline<N>::center() const {
    return c;
}

#endif // CUBIC_SPLINE_H
