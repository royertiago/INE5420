/* polynomial.test.cpp
 * Teste de unidade da classe Polynomial
 */

#include "math/polynomial.h"
#include "math/vector.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerDouble.h"
#include "test/lib/testerMatrix.h"

DECLARE_TEST( PolynomialTest ) {
    Test::TesterDouble t(2);
    Test::TesterMatrix m(2);
    using Math::Polynomial;
    using Math::Vector;
    bool b = true;

    Polynomial<double> p( new double[4]{0, 1, 0, 1}, 3 );
    // p(x) = x^3 + x
    b &= Test::TEST_EQUALS( p[0], 0.0 );
    b &= Test::TEST_EQUALS( p[1], 1.0 );
    b &= Test::TEST_EQUALS( p[2], 0.0 );
    b &= Test::TEST_EQUALS( p[3], 1.0 );

    b &= t.TEST_EQUALS( p(0), 0.0 );
    b &= t.TEST_EQUALS( p(1), 2.0 );
    b &= t.TEST_EQUALS( p(-1), -2.0 );
    b &= t.TEST_EQUALS( p(1.5), 4.875 );

    p = Polynomial<double>( new double[3]{2, -3, 1}, 2 );
    // p(x) = x^2 - 3x + 2

    b &= t.TEST_EQUALS( p(0), 2.0 );
    b &= t.TEST_EQUALS( p(1), 0.0 );
    b &= t.TEST_EQUALS( p(-1), 6.0 );
    b &= t.TEST_EQUALS( p(2), 0.0 );

    p = Polynomial<double>( new double[2]{-1.0, 3.0}, 1 );
    // p(x) = 3x - 1
    b &= t.TEST_EQUALS( p(0), -1.0 );
    b &= t.TEST_EQUALS( p(1), 2.0 );

    Vector<2> u{1.0, 1.0}, v{-1.0, -2.0};
    Polynomial<Vector<2>> q( new Vector<2>[2]{v, u - v}, 1 );
    // q(t) = (1-t) * v + t * u

    b &= m.TEST_EQUALS( q[0], v );
    b &= m.TEST_EQUALS( q[1], u-v );

    b &= m.TEST_EQUALS( q(0), v );
    b &= m.TEST_EQUALS( q(1), u );
    b &= m.TEST_EQUALS( q(0.5), (Vector<2>{0, -0.5}) );
    b &= m.TEST_EQUALS( q(1.5), (Vector<2>{2, 2.5}) );

    return b;
}
