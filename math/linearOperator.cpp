/* linearOperator.cpp
 * Contém as implementações das funções não templatizadas.
 */

#include <cmath>
using std::sin;
using std::cos;

#include "math/linearOperator.h"

using namespace Math;

LinearOperator<2> LinearFactory::Rotation2D( double d, Point<2> c ) {
    LinearOperator<2> o = Translation<2>( c );
    o.frontComposeWith( Rotation<2>( d, 0, 1 ) );
    o.frontComposeWith( Translation<2>( -c ) );
    return o;
}
