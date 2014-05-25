/* linearFactoryRotation3D.test.cpp
 * Teste de LinearFactory::Rotation3D
 */
#include "math/affineOperator.h"
#include "math/affineFactory.h"
#include "math/constant.h"
#include "test/lib/test.h"
#include "test/affineTester.h"

DECLARE_TEST( AffineFactoryRotation3DTest ) {
    bool b = true;
    Test::AffineTester m(2);
    using namespace Math;
    using namespace AffineFactory;
    Vector<3> x = {1, 0, 0};
    Vector<3> y = {0, 1, 0};
    Vector<3> z = {0, 0, 1};

    AffineOperator<3> op = Rotation3D( 1.5, y );
    b &= m.TEST_EQUALS( op, Rotation<3>(1.5, 2, 0) );
    b &= m.TEST_EQUALS( op.backComposeWith(Rotation3D( 1.5, -y )), 
                        Identity<3>() );

    op = Rotation3D( .5, z );
    b &= m.TEST_EQUALS( op, Rotation<3>(.5, 0, 1) );
    b &= m.TEST_EQUALS( op.backComposeWith(Rotation3D( .5, -z )), 
                        Identity<3>() );

    op = Rotation3D( 1, x );
    b &= m.TEST_EQUALS( op, Rotation<3>(1, 1, 2) );
    b &= m.TEST_EQUALS( op.backComposeWith(Rotation3D( 1, -x )),
                        Identity<3>() );

    op = Rotation3D( 8, {2, -8, 1.5} );
    b &= m.TEST_EQUALS( op.backComposeWith(Rotation3D( 8, {-2, 8, -1.5} )),
                        Identity<3>() );

    return b;
}
