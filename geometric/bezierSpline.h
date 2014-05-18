/* bezierSpline.h
 * Curva de Bézier.
 * Esta classe representa curvas de Bézier de ordem arbitrária;
 * para uma versão otimizada para curvas cúbicas, veja splineFactory.h.
 */
#ifndef BEZIER_SPLINE_H
#define BEZIER_SPLINE_H

#include <vector>
#include "math/interpolation.h"
#include "math/point.h"
#include "math/polynomial.h"
#include "render/renderer.h"
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
    std::vector<std::vector<Math::Polynomial<Math::Point<N>>>> polynomials;
    std::vector<Math::Point<N>> controlPoints;
    std::vector<std::vector<bool>> validPolynomials; // Memoização
    int order; // Ordem da spline

public:
    BezierSpline( std::vector<Math::Point<N>> controlPoints );
    
    BezierSpline( const BezierSpline& ) = default;
    BezierSpline( BezierSpline&& ) = default;
    BezierSpline<N>& operator=( const BezierSpline& ) = default;
    BezierSpline<N>& operator=( BezierSpline&& ) = default;
    ~BezierSpline() = default;

    /* Transforma um único ponto da spline.
     * Todos os segmentos serão reconstruídos. */
    void transformPoint( int index, const Math::LinearOperator<N>& );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual Math::Point<N> center() const override;
    virtual void transform( const Math::LinearOperator<N>& ) override;

private:
    /* Computa a curva de grau degree-1 do índice passado. */
    void calculate( int degreeMinusOne, int index );
};

template< int N >
BezierSpline<N>::BezierSpline( std::vector<Math::Point<N>> controlPoints ) :
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
        const Math::LinearOperator<N>& op )
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
    double sqnorm = 0.0;
    for( int i = 0; i < controlPoints.size() - 1; ++i )
        sqnorm += (controlPoints[i] - controlPoints[i+1]).sqnorm();

    int pixels = sqnorm * renderer->density();
    double delta = 400.0/pixels; // Mesma heuristica de cubicSpline.h
    auto it = p.iterator( 0, delta );
    Math::Vector<N> current = *it;
    ++it;
    Math::Vector<N> next = *it;
    for( ; it < 1; ++it, current = next, next = *it )
        renderer->drawLine( current, next );
}

template< int N >
Math::Point<N> BezierSpline<N>::center() const {
    Math::Point<N> center;
    for( const Math::Point<N>& p : controlPoints )
        center = center + p;
    return center * (1.0 / controlPoints.size() );
}
    
template< int N >
void BezierSpline<N>::transform( const Math::LinearOperator<N>& op ) {
    for( Math::Point<N>& p : controlPoints )
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
