/* splineGenerator.h
 * Tipo de função que recebe como parâmetro diversos
 * pontos de controle e devolve um polinômio de vetores.
 */
#ifndef SPLINE_GENERATOR_H
#define SPLINE_GENERATOR_H

#include <vector>
#include "math/vector.h"
#include "math/polynomial.h"

/* Curvas são, de acordo com a Matemática, funções que mapeiam
 * de um intervalo [a, b] para um espaço topológico qualquer,
 * no nosso caso R^n. PolynomialCurve<N> representará uma curva
 * polinomial que mapeia do intervalo [0, 1] para o R^N. */
template< int N >
using PolynomialCurve = Math::Polynomial< Math::Vector<N> >;

/* A mesma ideia pode ser aplicada a superfícies: uma superfície
 * polinomial é uma função que mapeia do quadrado [0, 1] x [0, 1]
 * para R^N. Este mapeamento é atingido iterando sobre uma
 * dimensão e produzindo curvas, que serão iteradas sobre a outra. */
template< int N >
using PolynomialSurface = Math::Polynomial< PolynomialCurve<N> >;

/* CurveGenerator<N> é uma função.
 * Seu único parâmetro é um std::vector< Math::Vector<N> >, os
 * pontos de controle.
 * Baseando-se neles, o SplineGenerator retorna um PolynomialCurve<N>.
 *
 * Exemplos de geradores de splines estão em splineFactoroy.h.
 */
template< int N >
using CurveGenerator = PolynomialCurve<N> 
    ( * )( std::vector< Math::Vector<N> > );

/* SurfaceGenerator<N> também é uma função.
 * Seu único parâmetro é um vetor de polinômios, as "curvas de controle".
 * Seu valor de retorno é uma superfície polinomial. */
template< int N >
using SurfaceGenerator = PolynomialSurface<N>
    ( * )( std::vector< Math::Polynomial<Math::Vector<N>> > );
#endif // SPLINE_GENERATOR_H
