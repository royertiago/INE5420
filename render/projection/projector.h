/* projector.h
 * Funções capazes de mapear pontos de coordenadas de window (ver window.h)
 * para coordenadas de window projetada.
 */
#ifndef PROJECTOR_H
#define PROJECTOR_H

#include "math/point.h"
#include "render/projection/projectedPoint.h"

/* Um Projector de dimensão N é uma função que toma por parâmetro
 * um ponto N-dimensional e retorna um ProjectedPoint que é a projeção
 * do ponto passado segundo seu método de projeção. */
template< int N >
using Projector = ProjectedPoint (*)( Math::Point<N> );

#endif // PROJECTOR_H
