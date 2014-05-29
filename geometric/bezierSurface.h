/* bezierSurface.h
 * Spline de superfície que generaliza Bézier.
 */
#ifndef BEZIER_SURFACE_H
#define BEZIER_SURFACE_H

#include <vector>
#include "geometric/splineGenerator.h"
#include "geometric/splineFactory.h"
#include "geometric/transformableObject.h"
#include "math/vector.h"
#include "math/polynomial.h"

template< int N >
class BezierSurface : public TransformableObject<N> {
    std::vector<std::vector<Math::Vector<N>>> cp; // [c]ontrol [p]oints
    Math::Polynomial<Math::Polynomial<Math::Vector<N>>> p; // [p]olynomial

public:
    /* Constrói uma superfície de Bézier a partir dos pontos de controle
     * passados.
     * O vetor deve ser não-nulo e todos os seus elementos devem ser
     * vetores não-nulos. */
    BezierSurface( std::vector<std::vector<Math::Vector<N>>> controlPoints );

    // Métodos herdados
    virtual void draw( Renderer<N>* ) override;
    virtual void transform( const Math::AffineOperator<N>& ) override;
    virtual Math::Vector<N> center() const override;

private:
    /* Recalcula o polinômio p. */
    void calculate();
};

// Implementação
template< int N >
BezierSurface<N>::BezierSurface( 
        std::vector<std::vector<Math::Vector<N>>> cp ) :
    cp( cp )
{
    calculate();
}

template< int N >
void BezierSurface<N>::draw( Renderer<N>* render ) {
    for( double x = 0; x <= 1; x += 0.1 )
        for( double y = 0; y < 1; y += 0.01 )
            render->drawLine( p(x)(y), p(x)(y+0.01) );

    for( double y = 0; y <= 1; y += 0.1 )
        for( double x = 0; x < 1; x += 0.01 )
            render->drawLine( p(x)(y), p(x+0.01)(y) );
}

template< int N >
void BezierSurface<N>::transform( const Math::AffineOperator<N>& op ) {
    for( auto& pv : cp )
        for( auto& v : pv )
            v = op (v);
    calculate();
}

template< int N >
Math::Vector<N> BezierSurface<N>::center() const {
    Math::Vector<N> r;
    int i = 0;
    for( const auto& pv : cp )
        for( const auto& v : pv ) {
            r = r + v;
            i++;
        }
    return r / i;
}

template< int N >
void BezierSurface<N>::calculate() {
    std::vector<Math::Polynomial<Math::Vector<N>>> ps;
    for( auto& pv : cp )
        ps.push_back( SplineFactory::Bezier( pv ) );
    p = SplineFactory::Bezier( ps );
}

#endif // BEZIER_SURFACE_H
