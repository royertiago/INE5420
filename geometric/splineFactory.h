/* splineFactory.h
 * Namespace que contém funções capazes de gerar splines cúbicas
 * a partir de vetores arbitrários.
 *
 * Note que as funções estão templatizadas para tipo: qualquer
 * classe que represente objetos de um espaço vetorial sobre
 * os números reais (double) pode ser utilizada.
 */
#ifndef SPLINE_FACTORY_H
#define SPLINE_FACTORY_H

#include "math/interpolation.h"
#include "math/polynomial.h"
#include "math/vector.h"

namespace SplineFactory {

    /* Gera uma curva cúbica de Bézier a partir dos pontos passados.
     * A curva interpolará os pontos p1 e p4 e tangenciará os segmentos
     * p1-p2 e p3-p4 nestes pontos, respectivamente. */
    template< typename Vec >
    Math::Polynomial<Vec> Bezier( Vec p1, Vec p2, Vec p3, Vec p4 );

    /* Constrói uma curva de Bézier a partir dos pontos passados.
     *
     * Ao contrário da função anterior, esta não está limitada a construir 
     * curvas de Bézier com grau 3, mas sim com qualquer grau arbitrário. */
    template< typename Vec >
    Math::Polynomial<Vec> Bezier( std::vector< Vec > );

    /* Gera uma curva de Hermite cujas extremidades são os pontos p1 e p4
     * e as tangentes são r1 e r4, respectivamente.
     *
     * A spline cúbica representará um polinômio cúbico s com coeficientes
     * vetoriais satisfazendo
     *   s(0) = p1
     *  s'(0) = r1
     *   s(1) = p4
     *  s'(1) = r4 */
    template< typename Vec >
    Math::Polynomial<Vec> Hermite( Vec p1, Vec r1, Vec p4, Vec r4 );

    /* Constrói uma curva cúbica de Hermite cujas extremidades serão
     * os pontos c[0] e c[2] e as tangentes serão c[1] e c[3].
     *
     * A função assume que c contém pelo menos quatro vetores. Vetores
     * adicionais são ignorados. */
    template< typename Vec >
    Math::Polynomial<Vec> Hermite( std::vector<Vec> c );

    /* Gera um segmento cúbico de uma B-Spline, a partir dos
     * pontos de controle especificados. */
    template< typename Vec >
    Math::Polynomial<Vec> BSpline( Vec p0, Vec p1, Vec p2, Vec p3 );

    /* Gera um segmento cúbigo de uma B-Spline, a partir dos
     * pontos de controle especificados.
     *
     * A função assube que c contém pelo menos quatro vetores.
     * Vetores adicionais são ignorados. */
    template< typename Vec >
    Math::Polynomial<Vec> BSpline( std::vector<Vec> c );


// Implementação

template< typename Vec >
Math::Polynomial<Vec> Bezier( Vec p1, Vec p2, Vec p3, Vec p4 )
{
    /* É possível demonstrar que uma curva de Bézier é uma
     * curva de Hermite com os mesmos pontos inicial e final,
     * com o vetor tangente r1 sendo 3*(p2 - p1) e o vetor
     * tangente r4 sendo 3*(p4 - p3). */
    return Hermite<Vec>( p1, (p2 - p1) * 3, p4, (p4 - p3) * 3 );
}

template< typename Vec >
Math::Polynomial<Vec> Bezier( std::vector< Vec > c ) {
    // Casos simples
    if( c.size() <= 1 ) // Constante
        return Math::Polynomial<Vec>( std::vector<Vec>{c} );
    if( c.size() == 2 ) // Linear
        return Interpolation::linear<Vec>( c[0], c[1] );
    if( c.size() == 3 ) // Quadrático
        return Interpolation::linear<Vec>( 
                Interpolation::linear<Vec>(c[0], c[1]), 
                Interpolation::linear<Vec>(c[1], c[2]) );

    /* Estas foram as curvas de Bézier de ordens 0, 1 e 2, respectivamente.
     * Uma curva de Bézier de ordem N cujos pontos de controle são
     * c[0], ..., c[N] é a interpolação linear das duas curvas de Bézier de
     * ordem N-1 cujos pontos de controle são c[0], ..., c[N-1] e
     * c[1], ..., c[N], respectivamente.
     *
     * No objeto bz, manteremos as curvas de Bézier das ordens já calculadas.
     * Usando a outra função, podemos acelerar o processo: começaremos
     * com as curvas cúbicas e cresceremos a ordem até chegar em c.size() - 1.
     */
    std::vector<std::vector<Math::Polynomial<Vec>>> bz(c.size()-3);
    /* Especificamente: bz[d] conterá todas as curvas de Bézier de grau d + 3.
     * bz[d][j] obedecerá aos pontos c[j], c[j+1], ..., c[j+d].
     */
    bz[0].resize( c.size() - 3 );
    for( unsigned j = 0; j < bz[0].size(); ++j )
        bz[0][j] = Bezier<Vec>( c[j], c[j+1], c[j+2], c[j+3] );

    for( unsigned d = 1; d < bz.size(); ++d ) {
        bz[d].resize( bz[d-1].size() - 1 );
        for( unsigned j = 0; j < bz[d].size(); ++j )
            bz[d][j] = Interpolation::linear( bz[d-1][j], bz[d-1][j+1] );
    }
    return bz[c.size()-4][0];
}

template< typename Vec >
Math::Polynomial<Vec> Hermite( Vec p1, Vec r1, Vec p4, Vec r4 )
{
    using Math::Matrix;
    using Math::Vector;
    static Matrix<4, 4> mh{{ 2, -2,  1,  1},
                           {-3,  3, -2, -1},
                           { 0,  0,  1,  0},
                           { 1,  0,  0,  0}};

    /* Dados os valores a, b, c, d, queremos obter coeficientes
     * e1, e2, e3 e e4 tais que, se s(t) = e1 * t^3 + e2 * t^2 + e3 * t + e4,
     * então s(0) = a, s(1) = b, s'(0) = c, s'(1) = d.
     *
     * Isto é, a, b, c, d impõem o valor inicial e final de s e da
     * derivada de s.
     *
     * Se G = {{a}, {b}, {c}, {d}}, isto é, G é um vetor com estes valores,
     * então mh satisfaz mh * G = {{e1}, {e2}, {e3}, {e4}}.
     *
     * Podemos extender este processo colocando vetores em G,
     * ao invés de coeficientes; isto é,
     *  a == p1
     *  b == p4
     *  c == r1
     *  d == r4 */
    Vector<4, Vec> G = {p1, p4, r1, r4};
    Vector<4, Vec> v = mh * G;
    return Math::Polynomial<Vec>( std::vector<Vec>{v[3], v[2], v[1], v[0]} );
}

template< typename Vec >
Math::Polynomial<Vec> Hermite( std::vector<Vec> v ) {
    return Hermite( v[0], v[1], v[2], v[3] );
}

template< typename Vec >
Math::Polynomial<Vec> BSpline( Vec p0, Vec p1, Vec p2, Vec p3 )
{
    using Math::Matrix;
    using Math::Vector;
    static Matrix<4, 4> mb = 
              Matrix<4, 4>{{-1,  3, -3,  1},
                           { 3, -6,  3,  0},
                           {-3,  0,  3,  0},
                           { 1,  4,  1,  0}} /6.0;

    Vector<4, Vec> G = {p0, p1, p2, p3};
    Vector<4, Vec> v = mb * G;
    return Math::Polynomial<Vec>( std::vector<Vec>{v[3], v[2], v[1], v[0]} );
}

template< typename Vec >
Math::Polynomial<Vec> BSpline( std::vector<Vec> v ) {
    return BSpline( v[0], v[1], v[2], v[3] );
}

} // namespace SplineFactory

#endif // SPLINE_FACTORY_H
