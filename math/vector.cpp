/* vector.cpp
 * Implementação dos métodos não-templatizados de vector.h
 */

#include "vector.h"
#include "debug.h"
using Math::Vector;

Vector<3> Math::crossProduct( Vector<3> u, Vector<3> v ) {
    return Vector<3>{ u[1]*v[2] - u[2]*v[1],
                      u[2]*v[0] - u[0]*v[2],
                      u[0]*v[1] - u[1]*v[0] };                        
}
