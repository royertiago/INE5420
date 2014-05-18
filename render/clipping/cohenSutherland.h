/* cohenSutherland.h
 * 
 * Algoritmo de clipping de linhas. Possui assinatura compatível
 * com a de clippingArea.h.
 */
#ifndef COHEN_SUTHERLAND_H
#define COHEN_SUTHERLAND_H

#include "render/projection/projectedPoint.h"

bool CohenSutherland( ProjectedPoint&, ProjectedPoint& );

#endif // COHEN_SUTHERLAND_H
