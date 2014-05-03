/* splineFactory.h
 * Namespace que contém funções capazes de gerar splines cúbicas
 * a partir de pontos arbitrários no espaço.
 */
#ifndef SPLINE_FACTORY_H
#define SPLINE_FACTORY_H

#include "math/point.h"
#include "math/vector.h"

namespace SplineFactory {

    /* Gera uma curva cúbica de Bézier a partir dos pontos passados.
     * A curva interpolará os pontos p1 e p4 e tangenciará os segmentos
     * p1-p2 e p3-p4 nestes pontos, respectivamente. */
    template< int N >
    CubicSpline<N> Bezier( Math::Point<N> p1, Math::Point<N> p2,
                           Math::Point<N> p3, Math::Point<N> p4 );

    /* Gera uma curva de Hermite cujas extremidades são os pontos p1 e p4
     * e as tangentes são r1 e r4, respectivamente.
     *
     * A spline cúbica representará um polinômio cúbico s com coeficientes
     * vetorias satisfazendo
     *   s(0) = p1
     *  s'(0) = r1
     *   s(1) = p4
     *  s'(1) = r4 */
    template< int N >
    CubicSpline<N> Hermite( Math::Point<N> p1, Math::Vector<N> r1, 
                            Math::Point<N> p4, Math::Vector<N> r4 );

    /* Gera um segmento de uma B-Spline cúbica, a partir dos
     * pontos de controle especificados. */
    template< int N >
    CubicSpline<N> BSpline( Math::Point<N> p0, Math::Point<N> p1, 
                            Math::Point<N> p2, Math::Point<N> p3 );


// Implementações

template< int N >
CubicSpline<N> Bezier( Math::Point<N> p1, Math::Point<N> p2,
                       Math::Point<N> p3, Math::Point<N> p4 )
{
    /* É possível demonstrar que uma curva de Bézier é uma
     * curva de Hermite com os mesmos pontos inicial e final,
     * com o vetor tangente r1 sendo 3*(p2 - p1) e o vetor
     * tangente r4 sendo 3*(p4 - p3). */
    return Hermite<N>( p1, (p2 - p1) * 3, p4, (p4 - p3) * 3 );
}

template< int N >
CubicSpline<N> Hermite( Math::Point<N> p1, Math::Vector<N> r1,
                        Math::Point<N> p4, Math::Vector<N> r4 )
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
    Matrix<4, N> G;
    for( int i = 0; i < N; ++i ) {
        G[0][i] = p1[i];
        G[1][i] = p4[i];
        G[2][i] = r1[i];
        G[3][i] = r4[i];
    }
    Matrix<4, N> C = mh * G; // C é a matriz dos coeficientes

    Vector<N> * c = new Vector<N>[4];
    // Estes coeficientes passaremos para a spline
    for( int i = 0; i < N; ++i ) {
        c[3][i] = C[0][i];
        c[2][i] = C[1][i];
        c[1][i] = C[2][i];
        c[0][i] = C[3][i];
        /* A sequência de atribuições está invertida pois o coeficiente
         * C[0] corresponde ao coeficiente e1, que está associado ao
         * termo de maior grau; para a classe CubicSpline, o coeficiente
         * do termo de maior grau é o último. */
    }

    return CubicSpline<N>( c, (p1 + p4) * 0.5 );
}

template< int N >
CubicSpline<N> BSpline( Math::Point<N> p0, Math::Point<N> p1, 
                        Math::Point<N> p2, Math::Point<N> p3 )
{
    using Math::Matrix;
    using Math::Vector;
    static Matrix<4, 4> mb = 
              Matrix<4, 4>{{-1,  3, -3,  1},
                           { 3, -6,  3,  0},
                           {-3,  0,  3,  0},
                           { 1,  4,  1,  0}} * (1.0/6.0);

    Matrix<4, N> G;
    for( int i = 0; i < N; ++i ) {
        G[0][i] = p0[i];
        G[1][i] = p1[i];
        G[2][i] = p2[i];
        G[3][i] = p3[i];
    }
    Matrix<4, N> C = mb * G;

    Vector<N> * c = new Vector<N>[4];
    for( int i = 0; i < N; ++i ) {
        c[3][i] = C[0][i];
        c[2][i] = C[1][i];
        c[1][i] = C[2][i];
        c[0][i] = C[3][i];
    }
    return CubicSpline<N>( c, (p0 + p3) * 0.5 );
}

} // namespace SplineFactory

#endif // SPLINE_FACTORY_H
