/* BSplineSurface.h
 * Spline de superfície que generaliza BSplines.
 */
#ifndef BSPLINE_SURFACE_H
#define BSPLINE_SURFACE_H

#include <vector>
#include "geometric/splineGenerator.h"
#include "geometric/splineFactory.h"
#include "geometric/transformableObject.h"
#include "math/vector.h"
#include "math/polynomial.h"

template< int N >
class BSplineSurface : public TransformableObject<N> {
    std::vector<std::vector<Math::Vector<N>>> cp; // [c]ontrol [p]oints
    std::vector<std::vector<PolynomialSurface<N>>> s; // [s]urfaces

public:
    /* Constrói uma superfície de Bézier a partir dos pontos de controle
     * passados.
     * O vetor deve ser não-nulo e ter tamanho maior ou igual a 4 e
     * todos os seus elementos devem ter o mesmo tamanho, que deve
     * ser maior ou igual a 4.
     * Isto é, no mínimo 16 pontos devem ser fornecidos. */
    BSplineSurface( std::vector<std::vector<Math::Vector<N>>> controlPoints );

    // Métodos herdados
    virtual void draw( Renderer<N>* ) override;
    virtual void transform( const Math::AffineOperator<N>& ) override;
    virtual Math::Vector<N> center() const override;

private:
    /* Recalcula o polinômio p. */
    void calculate();

    /* Desenha a superfície passada. */
    void draw( Renderer<N>*, const PolynomialSurface<N>& );
};

// Implementação
template< int N >
BSplineSurface<N>::BSplineSurface( 
        std::vector<std::vector<Math::Vector<N>>> cp ) :
    cp( cp ),
    s( cp.size() - 3, std::vector<PolynomialSurface<N>>( cp[0].size() - 3 ) )
{
    calculate();
}

template< int N >
void BSplineSurface<N>::draw( Renderer<N>* r, const PolynomialSurface<N>& s ) {
    for( double x = 0; x <= 1; x += 0.2 )
        for( double y = 0; y < 1; y += 0.01 )
            r->drawLine( s(x)(y), s(x)(y+0.01) );

    for( double y = 0; y <= 1; y += 0.2 )
        for( double x = 0; x < 1; x += 0.01 )
            r->drawLine( s(x)(y), s(x+0.01)(y) );
}

template< int N >
void BSplineSurface<N>::draw( Renderer<N>* r ) {
    for( const auto& alce : s )
        for( const auto& s : alce )
            draw( r, s );
}

template< int N >
void BSplineSurface<N>::transform( const Math::AffineOperator<N>& op ) {
    for( auto& pv : cp )
        for( auto& v : pv )
            v = op (v);
    calculate();
}

template< int N >
Math::Vector<N> BSplineSurface<N>::center() const {
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
void BSplineSurface<N>::calculate() {
    std::vector<std::vector<PolynomialCurve<N>>> cc( cp.size(),
            std::vector<PolynomialCurve<N>>( cp[0].size() - 3 ) );
    /* [c]ontrol [c]urves; cada linha da "matriz" cp será convertida
     * linha na matriz cc.
     * Como estas linhas serão construídas usando SplineFactory::BSpline,
     * seus tamanhos serão cp[0].size() - 3. */
    for( int i = 0; i < cc.size(); ++i )
        for( int j = 0; j < cc[i].size(); ++j )
            cc[i][j] = SplineFactory::BSpline(
                    cp[i][j], cp[i][j+1], cp[i][j+2], cp[i][j+3] );
    // Agora, iremos converter as colunas em superfícies:
    for( int i = 0; i + 3 < cc.size(); ++i )
        for( int j = 0; j < cc[i].size(); ++j )
            s[i][j] = SplineFactory::BSpline(
                    cc[i][j], cc[i+1][j], cc[i+2][j], cc[i+3][j] );
}

#endif // BSPLINE_SURFACE_H
