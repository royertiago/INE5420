/* perspective.h
 * Projeção em perspectiva para objetos tridimensionais. */
#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "math/vector.h"
#include "render/projection/projectedPoint.h"

ProjectedPoint perspective( Math::Vector<3> p );

#endif // PERSPECTIVE_H
