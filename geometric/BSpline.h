/* BSpline.h
 * Classe que agrupa diversos segmentos de B-Splines.
 *
 * Cada B-spline é identificada por quatro pontos de controle
 * adjacentes, portanto, com K pontos de controle, teremos K - 3
 * segmentos de B-Spline.
 */
#ifndef B_SPLINE_H
#define B_SPLINE_H

#include <vector>
#include "render/renderer.h"
#include "math/point.h"
#include "math/linearOperator.h"
#include "geometric/cubicSpline.h"
#include "geometric/splineFactory.h"
#include "geometric/transformableObject.h"

template< int N >
class BSpline : public TransformableObject<N> {
    std::vector<Math::Point<N>> controlPoints;
    std::vector<CubicSpline<N>> splines;

public:
    /* Constrói uma B-Spline a partir dos pontos de controle passados. */
    explicit BSpline( std::vector<Math::Point<N>> controlPoints );

    BSpline( const BSpline& ) = default;
    BSpline( BSpline&& ) = default;
    BSpline<N>& operator=( const BSpline& ) = default;
    BSpline<N>& operator=( BSpline&& ) = default;
    ~BSpline() = default;

    /* Transforma um único ponto da spline.
     * Os segmentos afetados serão reconstruídos. */
    void transformPoint( int index, const Math::LinearOperator<N>& );

    /* Adiciona um ponto de controle ao fim da spline. */
    void addPoint( Math::Point<N> );

    // Métodos herdados
    virtual void draw( Renderer * ) override;
    virtual Math::Point<N> center() const override;
    virtual void transform( const Math::LinearOperator<N>& ) override;

private:
    /* Recalcula o valor da B-Spline do índice passado. 
     * O índice será assumido valido. */
    void calculate( int index );
};

// Implementações
template< int N >
BSpline<N>::BSpline( std::vector<Math::Point<N>> controlPoints ) :
    controlPoints( controlPoints ),
    splines()
{
    splines.reserve( controlPoints.size() - 3 );
    for( int i = 0; i < controlPoints.size() - 3; ++i )
        splines.emplace_back( SplineFactory::BSpline<N>( controlPoints[i], 
                controlPoints[i+1], controlPoints[i+2], controlPoints[i+3] ) );
}

template< int N >
void BSpline<N>::transformPoint( int n, const Math::LinearOperator<N>& op ) {
    controlPoints[n] = op( controlPoints[n] );
    for( int i = n - 3; i <= n && i < splines.size(); ++i )
        calculate( i );
}

template< int N >
void BSpline<N>::addPoint( Math::Point<N> p ) {
    controlPoints.push_back( p );
    int i = controlPoints.size() - 4;
    splines.emplace_back( SplineFactory::BSpline<N>( controlPoints[i],
            controlPoints[i+1], controlPoints[i+2], controlPoints[i+3] ) );
}

template< int N >
void BSpline<N>::draw( Renderer * renderer ) {
    for( CubicSpline<N>& s : splines )
        s.draw( renderer );
}

template< int N >
Math::Point<N> BSpline<N>::center() const {
    Math::Point<N> center;
    for( const Math::Point<N>& p : controlPoints )
        center = center + p;
    return center * (1.0 / controlPoints.size() );
}

template< int N >
void BSpline<N>::transform( const Math::LinearOperator<N>& op ) {
    for( Math::Point<N>& p : controlPoints )
        p = op( p );
    for( int i = 0; i < splines.size(); ++i )
        calculate( i );
}

template< int N >
void BSpline<N>::calculate( int i ) {
    splines[i] = SplineFactory::BSpline<N>( controlPoints[i],
        controlPoints[i+1], controlPoints[i+2], controlPoints[i+3] );
}

#endif // B_SPLINE_H
