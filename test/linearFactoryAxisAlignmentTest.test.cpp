/* linearFactoryAxisAlignmentTest.test.cpp
 * Teste de unidade para as funções LinearFactory::AxisAlignment e
 * LinearFactory::InverseAxisAlignment.
 */

#include "math/linearOperator.h"

#include "math/constant.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerMatrix.h"

DECLARE_TEST( LinearFactoryAxisAlignmentTest ) {
    bool b = true;
    Test::TesterMatrix m(2);
    using namespace Math;
    using namespace LinearFactory;
    Vector<3> x = {1, 0, 0};
    Vector<3> y = {0, 1, 0};
    Vector<3> z = {0, 0, 1};

    //  Não precisa alinhar nada; já está tudo alinhado.
    LinearOperator<3> op = AxisAlignment( z, y );
    b &= m.TEST_EQUALS( op, Scale<3>(1) );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( z, y ), Scale<3>(1) );

    // view-up aponta para o eixo x em vez de para cima.
    op = AxisAlignment( z, x );
    b &= m.TEST_EQUALS( op, Rotation<3>(PI/2, 0, 1) );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( z, x ), Scale<3>(1) );

    // view-up aponta para o eixo x no sentido negativo.
    op = AxisAlignment( z, -x );
    b &= m.TEST_EQUALS( op, Rotation<3>(PI/2, 1, 0) );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( z, -x ), Scale<3>(1) );

    // front aponta para eixo x e view-up para z.
    LinearOperator<3> ex = Rotation<3>(PI/2, 0, 2 ); //[ex]pected
    ex.backComposeWith( Rotation<3>(PI/2, 1, 0 ) );
    op = AxisAlignment( x, z );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( x, z ), Scale<3>(1) );

    // front aponta para eixo x no sentido contrário e view-up para z.
    ex = Rotation<3>(PI/2, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 0, 1 ) );
    op = AxisAlignment( -x, z );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( -x, z ), Scale<3>(1) );

    // front aponta para eixo x e view-up para z no sentido contrário
    ex = Rotation<3>(PI/2, 0, 2 );
    ex.backComposeWith( Rotation<3>(PI/2, 0, 1 ) );
    op = AxisAlignment( x, -z );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( x, -z ), Scale<3>(1) );

    // front aponta para eixo x e view-up para z, ambos no sentido contrário
    ex = Rotation<3>(PI/2, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 1, 0 ) );
    op = AxisAlignment( -x, -z );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( -x, -z ), Scale<3>(1) );

    // front e view-up nas direções corretas, mas sentido contrário
    ex = Rotation<3>(PI, 1, 2 );
    op = AxisAlignment( -z, -y );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( -z, -y ), Scale<3>(1) );

    // front apontando para -z-x, up apontando para x-z
    ex = Rotation<3>(3*PI/4, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 1, 0) );
    op = AxisAlignment( -z-x, x-z );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( -z-x, x-z ), Scale<3>(1) );

    // front apontando para -z-x, up apontando para -y
    ex = Rotation<3>(3*PI/4, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI, 1, 0) );
    op = AxisAlignment( -z-x, -y );
    b &= m.TEST_EQUALS( op, ex );
    b &= m.TEST_EQUALS( op * InverseAxisAlignment( -z-x, -y ), Scale<3>(1) );

    return b;
}
