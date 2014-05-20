/* perspective.h
 * Projeção em perspectiva para objetos tridimensionais. */
#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "math/point.h"
#include "render/projection/projectedPoint.h"

ProjectedPoint perspective( Math::Point<3> p );

#endif // PERSPECTIVE_H
