/* linearFactoryRotation3D.test.cpp
 * Teste de LinearFactory::Rotation3D
 */
#include "math/linearOperator.h"

#include "math/constant.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerMatrix.h"

DECLARE_TEST( LinearFactoryRotation3DTest ) {
    bool b = true;
    Test::TesterMatrix m(4);
    using namespace Math;
    using namespace LinearFactory;
    Vector<3> x = {1, 0, 0};
    Vector<3> y = {0, 1, 0};
    Vector<3> z = {0, 0, 1};

    LinearOperator<3> op = Rotation3D( 1.5, y );
    b &= m.TEST_EQUALS( op, Rotation<3>(1.5, 2, 0) );
    b &= m.TEST_EQUALS( op * Rotation3D( 1.5, -y ), Scale<3>(1) );

    op = Rotation3D( .5, z );
    b &= m.TEST_EQUALS( op, Rotation<3>(.5, 0, 1) );
    b &= m.TEST_EQUALS( op * Rotation3D( .5, -z ), Scale<3>(1) );

    op = Rotation3D( 1, x );
    b &= m.TEST_EQUALS( op, Rotation<3>(1, 1, 2) );
    b &= m.TEST_EQUALS( op * Rotation3D( 1, -x ), Scale<3>(1) );

    op = Rotation3D( 8, {2, -8, 1.5} );
    b &= m.TEST_EQUALS( op * Rotation3D( 8, {-2, 8, -1.5} ), Scale<3>(1) );

    return b;
}
