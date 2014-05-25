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
#include "math/vector.h"
#include "math/affineOperator.h"
#include "geometric/cubicSpline.h"
#include "geometric/splineFactory.h"
#include "geometric/transformableObject.h"

template< int N >
class BSpline : public TransformableObject<N> {
    std::vector<Math::Vector<N>> controlPoints;
    std::vector<CubicSpline<N>> splines;

public:
    /* Constrói uma B-Spline a partir dos pontos de controle passados. */
    explicit BSpline( std::vector<Math::Vector<N>> controlPoints );

    /* Transforma um único ponto da spline.
     * Os segmentos afetados serão reconstruídos. */
    void transformPoint( int index, const Math::AffineOperator<N>& );

    /* Adiciona um ponto de controle ao fim da spline. */
    void addPoint( Math::Vector<N> );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual Math::Vector<N> center() const override;
    virtual void transform( const Math::AffineOperator<N>& ) override;

private:
    /* Recalcula o valor da B-Spline do índice passado. 
     * O índice será assumido valido. */
    void calculate( int index );
};

// Implementações
template< int N >
BSpline<N>::BSpline( std::vector<Math::Vector<N>> controlPoints ) :
    controlPoints( controlPoints ),
    splines()
{
    splines.reserve( controlPoints.size() - 3 );
    for( int i = 0; i < controlPoints.size() - 3; ++i )
        splines.emplace_back( SplineFactory::BSpline<N>( controlPoints[i], 
                controlPoints[i+1], controlPoints[i+2], controlPoints[i+3] ) );
}

template< int N >
void BSpline<N>::transformPoint( int n, const Math::AffineOperator<N>& op ) {
    controlPoints[n] = op( controlPoints[n] );
    for( int i = n - 3; i <= n && i < splines.size(); ++i )
        calculate( i );
}

template< int N >
void BSpline<N>::addPoint( Math::Vector<N> p ) {
    controlPoints.push_back( p );
    int i = controlPoints.size() - 4;
    splines.emplace_back( SplineFactory::BSpline<N>( controlPoints[i],
            controlPoints[i+1], controlPoints[i+2], controlPoints[i+3] ) );
}

// Métodos herdados

template< int N >
void BSpline<N>::draw( Renderer<N> * renderer ) {
    for( CubicSpline<N>& s : splines )
        s.draw( renderer );
}

template< int N >
Math::Vector<N> BSpline<N>::center() const {
    Math::Vector<N> center;
    for( const Math::Vector<N>& p : controlPoints )
        center = center + p;
    return center / controlPoints.size();
}

template< int N >
void BSpline<N>::transform( const Math::AffineOperator<N>& op ) {
    for( Math::Vector<N>& p : controlPoints )
        p = op( p );
    for( int i = 0; i < splines.size(); ++i )
        calculate( i );
}

// Métodos privados

template< int N >
void BSpline<N>::calculate( int i ) {
    splines[i] = SplineFactory::BSpline<N>( controlPoints[i],
        controlPoints[i+1], controlPoints[i+2], controlPoints[i+3] );
}

#endif // B_SPLINE_H
