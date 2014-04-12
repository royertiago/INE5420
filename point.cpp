/* point.cpp
 * Implementação de point.h */

#include <algorithm>

#include "point.h"
#include "matrix.h"

using Math::Vector;

template< int N >
Point<N>::Point( const Vector<N>& source ) {
    std::copy( vector.begin(), vector.end(), source.begin() );
    vector[N] = 1.0;
}
