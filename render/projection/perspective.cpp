/* perspective.cpp
 * Implementação de perspective.h
 */
#include "perspective.h"

ProjectedPoint perspective( Math::Point<3> p ) {
    return ProjectedPoint{ p[0]/p[2], p[1]/p[2] };
}
