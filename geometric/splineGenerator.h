/* splineGenerator.h
 * Tipo de função que recebe como parâmetro diversos
 * pontos de controle e devolve um polinômio de vetores.
 */
#ifndef SPLINE_GENERATOR_H
#define SPLINE_GENERATOR_H

/* SplineGenerator<N> é uma função.
 * Seu único parâmetro é um std::vector< Math::Vector<N> >, os
 * pontos de controle.
 * Baseando-se neles, o SplineGenerator retorna um
 * Math::Polynomial< Math::Vector<N> >.
 *
 * Exemplos de geradores de splines estão em splineFactoroy.h.
 */
template< int N >
using SplineGenerator = Math::Polynomial< Math::Vector<N> >
    ( * )( std::vector< Math::Vector<N> > );

#endif // SPLINE_GENERATOR_H
