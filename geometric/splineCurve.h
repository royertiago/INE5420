/* splineCurve.h
 * Curva unidimensional polinomial genérica.
 * 
 * Objetos desta classe agrupam vários polinômios vetoriais criados
 * com SplineGenerator e as desenha na tela.
 *
 * Esta classe é parametrizada, em tempo de execução, por dois inteiros:
 * size e step (tamanho e passo da spline). Dado um conjunto de pontos de 
 * controle, este objeto gera polinômios a partir de subconjuntos destes 
 * pontos.
 * O primeiro polinômio é gerado com os pontos 0, 1, ..., size - 1.
 * O segundo é gerado com os pontos step, step+1,..., step + size - 1.
 * O n-ésimo é gerado com os pontos (n-1)*step, ..., (n-1)*step + size - 1.
 * 
 * Por exemplo, B-Splines são especificadas com size = 4, step = 1.
 * Curvas de Hermite podem ser especificadas com size = 4, step = 2,
 * intercalando pontos de controle e vetores tangentes.
 *
 * Os pontos são usados até atingir a quantidade total de pontos;
 * no exemplo das curvas de Hermite, com 5 pontos de controle, serão
 * gerados apenas um polinômio, com os 4 primeiros pontos. O último
 * será ignorado.
 *
 * Caso step == 0, apenas um segmento de spline será gerado, com os
 * primeiros size pontos de controle. Caso size == 0, todos os pontos 
 * de controle serão usados.
 * Isto permite que curvas de Bézier de grau arbitrário sejam
 * implementadas usando size == step == 0. 
 */
#ifndef SPLINE_CURVE_H
#define SPLINE_CURVE_H

#include <vector>
#include "math/polynomial.h"
#include "math/vector.h"
#include "geometric/transformableObject.h"
#include "geometric/splineGenerator.h"
#include "render/renderer.h"

template< int N >
class SplineCurve : public TransformableObject<N> {
    std::vector<Math::Vector<N>> cp; // [c]ontrol [p]oints
    SplineGenerator<N> sg;
    int size, step;
    std::vector<Math::Polynomial<Math::Vector<N>>> p;

public:
    /* Constrói uma spline com os referidos pontos de controle,
     * a partir do gerador de splines especificado, de acordo
     * com a descrição acima. */
    SplineCurve( std::vector<Math::Vector<N>> controlPoints, 
            SplineGenerator<N> sg, int size, int step );

    // Métodos herdados
    virtual void draw( Renderer<N> * ) override;
    virtual void transform( const Math::AffineOperator<N>& ) override;
    /* O centro é calculado a partir da média aritmética dos
     * vetores que estão nas posições múltiplas de step. */
    virtual Math::Vector<N> center() const override;

private:
    // Métodos auxiliares
    /* Desenha o polinômio passado na tela. */
    void draw( Renderer<N>*, Math::Polynomial<Math::Vector<N>>& );

    /* Recalcula todos os polinômios. */
    void calculate();
};

// Implementação
template< int N >
SplineCurve<N>::SplineCurve( std::vector<Math::Vector<N>> controlPoints, 
                             SplineGenerator<N> sg, int size, int step ) :
    cp( controlPoints ),
    sg( sg ),
    size( size ),
    step( step ),
    p( step == 0 ? 1 : (controlPoints.size()-size) / step + 1)
{
    calculate();
    /* TODO: se adicionar algum método addPoint, testar se a conta acima
     * está correta. */
}

template< int N >
void SplineCurve<N>::draw( Renderer<N> * renderer, 
        Math::Polynomial<Math::Vector<N>>& p ) {
    double snorm = 1.0;
    for( int i = 1; i <= p.degree(); ++i )
        snorm += norm( p[i] );
    /* Heurística provavelmente falha: como teremos uma combinação
     * linear dos vetores p[i] cujos coeficientes estão enttre 0 e 1,
     * esperamos que o comprimento da curva não seja muito maior
     * do que a soma das normas dos coeficientes intermediários. */
    //double delta = 1.0/ ((int) snorm * renderer->density()/100 );
    double delta = 1e-2; // TODO: achar heurística decente.

    auto it = p.iterator( 0, delta );
    Math::Vector<N> current = *it;
    ++it;
    Math::Vector<N> next = *it;
    for( ; it < 1; ++it, current = next, next = *it )
        renderer->drawLine( current, next );
}

template< int N >
void SplineCurve<N>::draw( Renderer<N> * renderer ) {
    for( auto& polynomial : p ) {
        draw( renderer, polynomial );
    }
}

template< int N >
void SplineCurve<N>::transform( const Math::AffineOperator<N>& op ) {
    for( auto& point : cp )
        point = op( point );
    calculate();
}

template< int N >
Math::Vector<N> SplineCurve<N>::center() const {
    Math::Vector<N> r;
    unsigned i = 0, j = 0;
    for( ; i < cp.size(); i += (step == 0 ? 1 : step), ++j )
        r = r + cp[i];
    return r / j;
}

// Método privado
template< int N >
void SplineCurve<N>::calculate() {
    if( step == 0 ) // TODO: separar em várias classes
        if( size == 0 )
            p[0] = sg( cp );
        else
            p[0] = sg( std::vector<Math::Vector<N>>( &cp[0], &cp[0] + size ) );
    else
        for( unsigned i = 0, b = 0; b + size <= cp.size(); ++i, b += step )
            p[i] = sg( std::vector<Math::Vector<N>>( &cp[b], &cp[b] + size ) );
}

#endif // SPLINE_CURVE_H
