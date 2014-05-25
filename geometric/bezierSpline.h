/* bezierSpline.h
 * Curva de Bézier.
 * Esta classe representa curvas de Bézier de ordem arbitrária;
 * para uma versão otimizada para curvas cúbicas, veja splineFactory.h.
 */
#ifndef BEZIER_SPLINE_H
#define BEZIER_SPLINE_H

#include <vector>
#include "math/interpolation.h"
#include "math/vector.h"
#include "math/polynomial.h"
#include "geometric/transformableObject.h"

template< int N >
class BezierSpline : public TransformableObject<N> {
    /* Uma curva de Bézier de ordem N é a interpolação linear de
     * duas curvas de Bézier de ordem N-1. Manteremos aqui todos
     * os polinômios gerados no processo.
     *
     * A curva de Bézier polynomials[0][i] interpolará os pontos
     * controlPoints[i] e controlPoints[i+1].
     * A curva de Bézier polynomials[k][i] interpolará os polinômios
     * polynomials[k-1][i] e polynomials[k-1][i+1].
     *
     * Para K pontos de controle, precisaremos, portanto, de K-1
     * ordens de curvas salvas. */
    std::vector<std::vector<Math::Polynomial<Math::Vector<N>>>> polynomials;
    std::vector<Math::Vector<N>> controlPoints;
    std::vector<std::vector<bool>> validPolynomials; // Memoização
    int order; // Ordem da spline

public:
    BezierSpline( std::vector<Math::Vector<N>> controlPoints );
    
    /* Transforma um único ponto da spline.
     * Todos os segmentos serão reconstruídos. */
    void transformPoint( int index, const Math::AffineOperator<N>& );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual Math::Vector<N> center() const override;
    virtual void transform( const Math::AffineOperator<N>& ) override;

private:
    /* Computa a curva de grau degree-1 do índice passado. */
    void calculate( int degreeMinusOne, int index );
};

template< int N >
BezierSpline<N>::BezierSpline( std::vector<Math::Vector<N>> controlPoints ) :
    polynomials( controlPoints.size() - 1 ),
    controlPoints( controlPoints ),
    validPolynomials( controlPoints.size() - 1 )
{
    for( int i = 0; i < controlPoints.size() - 1; ++i ) {
        polynomials[0].emplace_back( 
                Interpolation::linear( controlPoints[i], controlPoints[i+1] ));
        validPolynomials[0].push_back( true );
    }
    for( int d = 1; d < controlPoints.size() - 1; ++d )
        for( int i = 0; i < polynomials[d-1].size() - 1; ++i ) {
            polynomials[d].emplace_back( Interpolation::linear( 
                        polynomials[d-1][i], polynomials[d-1][i+1] ) );
            validPolynomials[d].push_back( true );
        }
    order = controlPoints.size() - 1;
}

template< int N >
void BezierSpline<N>::transformPoint( int index, 
        const Math::AffineOperator<N>& op )
{
    controlPoints[index] = op( controlPoints[index] );
    for( auto& valid : validPolynomials )
        for( int i = 0; i < valid.size(); ++i )
            valid[i] = false;
    calculate( order - 1, 0 );
}

// Métodos herdados

template< int N >
void BezierSpline<N>::draw( Renderer<N> * renderer ) {
    auto& p = polynomials[order-1][0];
    double snorm = 0.0;
    for( int i = 0; i < controlPoints.size() - 1; ++i )
        snorm += norm(controlPoints[i] - controlPoints[i+1]);

    int pixels = snorm * renderer->density();
    double delta = 100.0/pixels; // Mesma heuristica de cubicSpline.h

    auto it = p.iterator( 0, delta );
    Math::Vector<N> current = *it;
    ++it;
    Math::Vector<N> next = *it;
    for( ; it < 1; ++it, current = next, next = *it )
        renderer->drawLine( current, next );
}

template< int N >
Math::Vector<N> BezierSpline<N>::center() const {
    Math::Vector<N> center;
    for( const Math::Vector<N>& p : controlPoints )
        center = center + p;
    return center / controlPoints.size();
}
    
template< int N >
void BezierSpline<N>::transform( const Math::AffineOperator<N>& op ) {
    for( Math::Vector<N>& p : controlPoints )
        p = op( p );
    for( auto& valid : validPolynomials )
        for( int i = 0; i < valid.size(); ++i )
            valid[i] = false;
    calculate( order - 1, 0 );
}

// Métodos privados

template< int N >
void BezierSpline<N>::calculate( int order, int index ) {
    if( validPolynomials[order][index] )
        return;
    if( order == 0 ) // Lembrando que order é degreeMinusOne
        polynomials[order][index] = Interpolation::linear(
                controlPoints[index], controlPoints[index+1] );
    else {
        calculate( order - 1, index );
        calculate( order - 1, index + 1 );
        polynomials[order][index] = Interpolation::linear(
                polynomials[order-1][index], polynomials[order-1][index+1] );
    }
    validPolynomials[order][index] = true;
}

#endif // BEZIER_SPLINE_H
