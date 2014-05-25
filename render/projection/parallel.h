/* parallel.h
 * Funcão de projeção que ignora as dimensões adicionais do ponto
 * a ser projetado.
 *
 * Para pontos bidimensionais, este tipo de projeção meramente
 * traduz Point<2> para ProjectedPoint.
 *
 * A assinatura é compatível com a de um Projector.
 */
#ifndef PARALLEL_H
#define PARALLEL_H

#include "math/vector.h"
#include "render/projection/projectedPoint.h"

template< int N >
ProjectedPoint parallel( Math::Vector<N> p ) {
    static_assert( N > 1, "Não é possível projetar de menos de 2 dimensões" );
    return ProjectedPoint{ p[0], p[1] };
}

#endif // PARALLEL_H
