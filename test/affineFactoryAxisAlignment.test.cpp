/* linearFactoryAxisAlignment.test.cpp
 * Teste de unidade para as funções AffineFactory::AxisAlignment e
 * AffineFactory::InverseAxisAlignment.
 */

#include "math/affineFactory.h"

#include "math/constant.h"
#include "test/lib/test.h"
#include "test/affineTester.h"

DECLARE_TEST( AffineFactoryAxisAlignmentTest ) {
    bool b = true;
    Test::AffineTester m(2);
    using namespace Math;
    using namespace AffineFactory;
    Vector<3> x = {1, 0, 0};
    Vector<3> y = {0, 1, 0};
    Vector<3> z = {0, 0, 1};

    //  Não precisa alinhar nada; já está tudo alinhado.
    AffineOperator<3> op = AxisAlignment( z, y );
    b &= m.TEST_EQUALS( op, Identity<3>() );

    // view-up aponta para o eixo x em vez de para cima.
    op = AxisAlignment( z, x );
    b &= m.TEST_EQUALS( op, Rotation<3>(PI/2, 0, 1) );

    // view-up aponta para o eixo x no sentido negativo.
    op = AxisAlignment( z, -x );
    b &= m.TEST_EQUALS( op, Rotation<3>(PI/2, 1, 0) );

    // front aponta para eixo x e view-up para z.
    AffineOperator<3> ex = Rotation<3>(PI/2, 0, 2 ); //[ex]pected
    ex.backComposeWith( Rotation<3>(PI/2, 1, 0 ) );
    op = AxisAlignment( x, z );
    b &= m.TEST_EQUALS( op, ex );

    // front aponta para eixo x no sentido contrário e view-up para z.
    ex = Rotation<3>(PI/2, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 0, 1 ) );
    op = AxisAlignment( -x, z );
    b &= m.TEST_EQUALS( op, ex );

    // front aponta para eixo x e view-up para z no sentido contrário
    ex = Rotation<3>(PI/2, 0, 2 );
    ex.backComposeWith( Rotation<3>(PI/2, 0, 1 ) );
    op = AxisAlignment( x, -z );
    b &= m.TEST_EQUALS( op, ex );

    // front aponta para eixo x e view-up para z, ambos no sentido contrário
    ex = Rotation<3>(PI/2, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 1, 0 ) );
    op = AxisAlignment( -x, -z );
    b &= m.TEST_EQUALS( op, ex );

    // front e view-up nas direções corretas, mas sentido contrário
    ex = Rotation<3>(PI, 1, 2 );
    op = AxisAlignment( -z, -y );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para -z-x, up apontando para x-z
    ex = Rotation<3>(3*PI/4, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 1, 0) );
    op = AxisAlignment( -z-x, x-z );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para -z-x, up apontando para -y
    ex = Rotation<3>(3*PI/4, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI, 1, 0) );
    op = AxisAlignment( -z-x, -y );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para -z-x, up apontando para y
    ex = Rotation<3>(3*PI/4, 2, 0 );
    op = AxisAlignment( -z-x, y );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para -x-y-z, up apontando para 2y-x-z
    ex = Rotation<3>(3*PI/4, 2, 0 );
    ex.backComposeWith( Rotation<3>( atan(1/sqrt(2)), 2, 1 ) );
    op = AxisAlignment( -x-y-z, y*2-x-z );
    b &= m.TEST_EQUALS( op, ex );

    return b;
}
