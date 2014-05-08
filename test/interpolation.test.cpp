/* interpolation.test.cpp
 * Teste de unidade das funcões de math/interpolation.h */

#include "math/interpolation.h"
#include "math/vector.h"
#include "math/polynomial.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerMatrix.h"
#include "test/lib/testerDouble.h"

DECLARE_TEST( InterpolationTest ) {
    bool b = true;
    Test::TesterDouble d(2);

    Math::Polynomial<double> p = Interpolation::linear( 1.0, 2.0 );
    b &= d.TEST_EQUALS( p[0], 1 );
    b &= d.TEST_EQUALS( p[1], 1 );

    p = Interpolation::linear(
            Math::Polynomial<double>( new double[2]{1, -1}, 1 ),
            Math::Polynomial<double>( new double[2]{1, 1}, 1 ) );

    b &= d.TEST_EQUALS( p[0], 1 );
    b &= d.TEST_EQUALS( p[1], -1 );
    b &= d.TEST_EQUALS( p[2], 2 );

    return b;
}
