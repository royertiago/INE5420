/* interpolation.test.cpp
 * Teste de unidade das funcões de math/interpolation.h */

#include <vector>

#include "math/interpolation.h"
#include "math/polynomial.h"
#include "test/lib/test.h"

DECLARE_TEST( InterpolationTest ) {
    bool b = true;
    Test::TesterDouble d(2);

    Math::Polynomial<double> p = Interpolation::linear( 1.0, 2.0 );
    b &= d.TEST_EQUALS( p[0], 1 );
    b &= d.TEST_EQUALS( p[1], 1 );

    p = Interpolation::linear(
            Math::Polynomial<double>( std::vector<double>{1, -1} ),
            Math::Polynomial<double>( std::vector<double>{1,  1} ) );

    b &= d.TEST_EQUALS( p[0], 1 );
    b &= d.TEST_EQUALS( p[1], -1 );
    b &= d.TEST_EQUALS( p[2], 2 );

    return b;
}
