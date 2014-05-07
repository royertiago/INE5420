/* hermite.h
 * Classe que agrupa vários segmentos de splines de Hermite.
 */
#ifndef HERMITE_SPLINE_H
#define HERMITE_SPLINE_H

#include <vector>
#include "geometric/cubicSpline.h"
#include "geometric/splineFactory.h"
#include "geometric/transformableObject.h"
#include "math/point.h"
#include "math/vector.h"
#include "render/renderer.h"

template< int N >
class HermiteSpline : public TransformableObject<N> {
    std::vector<Math::Point<N>> controlPoints;
    std::vector<Math::Vector<N>> tangentVectors;
    std::vector<CubicSpline<N>> splines;

public:
    /* Constrói uma curva de Hermite a partir dos pontos de controle
     * passados, com os respectivos vetores tangente.
     * Assumiremos que estes vetores possuem o mesmo tamanho, e
     * maior que 1. */
    HermiteSpline( std::vector<Math::Point<N>> controlPoints,
                  std::vector<Math::Vector<N>> tangentVectors );

    HermiteSpline( const HermiteSpline& ) = default;
    HermiteSpline( HermiteSpline&& ) = default;
    HermiteSpline& operator=( const HermiteSpline& ) = default;
    HermiteSpline& operator=( HermiteSpline&& ) = default;

    /* Transforma um único ponto da spline.
     * Os segmentos afetados serão reconstruídos. */
    void transformPoint( int index, const Math::LinearOperator<N>& );

    /* Adiciona mais um ponto à curva de hermite, com o vetor
     * tangente passado. */
    void addPoint( Math::Point<N> controlPoint, Math::Vector<N> tangent );

    // Métodos herdados
    virtual void draw( Renderer * ) override;
    virtual Math::Point<N> center() const override;
    virtual void transform( const Math::LinearOperator<N>& ) override;

private:
    /* Recalcula o valor da spline de Hermite do índice passado. 
     * O índice será assumido valido. */
    void calculate( int index );
};

// Implementações
template< int N >
HermiteSpline<N>::HermiteSpline( std::vector<Math::Point<N>> controlPoints,
        std::vector<Math::Vector<N>> tangentVectors ) :
    controlPoints( controlPoints ),
    tangentVectors( tangentVectors ),
    splines()
{
    splines.reserve( controlPoints.size() - 1 );
    for( int i = 0; i < controlPoints.size() - 1; ++i )
        splines.emplace_back( SplineFactory::Hermite<N>( 
                    controlPoints[i], tangentVectors[i],
                  controlPoints[i+1], tangentVectors[i+1] ) );
}

template< int N >
void HermiteSpline<N>::transformPoint( int n, 
        const Math::LinearOperator<N>& op )
{
    controlPoints[n] = op( controlPoints[n] );
    tangentVectors[n] = Math::Vector<N>( op( Math::Point<N>(
                    tangentVectors[ n ] ) ) );
    calculate( n );
    if( n + 1 < splines.size() )
        calculate( n + 1 );
}

template< int N >
void HermiteSpline<N>::addPoint( Math::Point<N> p, Math::Vector<N> v ) {
    controlPoints.push_back( p );
    tangentVectors.push_back( v );
    int i = controlPoints.size() - 2;
    splines.emplace_back( SplineFactory::Hermite<N>( 
                controlPoints[i], tangentVectors[i],
              controlPoints[i+1], tangentVectors[i+1] ) );
}

template< int N >
void HermiteSpline<N>::draw( Renderer * renderer ) {
    for( CubicSpline<N>& s : splines )
        s.draw( renderer );
}

template< int N >
Math::Point<N> HermiteSpline<N>::center() const {
    Math::Point<N> center;
    for( const Math::Point<N>& p : controlPoints )
        center = center + p;
    return center * (1.0 / controlPoints.size() );
}

template< int N >
void HermiteSpline<N>::transform( const Math::LinearOperator<N>& op ) {
    for( Math::Point<N>& p : controlPoints )
        p = op( p );
    for( int i = 0; i < splines.size(); ++i )
        calculate( i );
}

template< int N >
void HermiteSpline<N>::calculate( int i ) {
    splines[i] = SplineFactory::Hermite<N>(
            controlPoints[i], tangentVectors[i],
          controlPoints[i+1], tangentVectors[i+1] );
}

#endif // HERMITE_SPLINE_H
