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

    //  Não precisa alinhar nada; já está tudo alinhado.
    LinearOperator<3> op = AxisAlignment( {0, 0, 1}, {1, 0, 0} );
    b &= m.TEST_EQUALS( op, Scale<3>(1) );

    // view-up aponta para o eixo y em vez de para cima.
    op = AxisAlignment( {0, 0, 1}, {0, 1, 0} );
    b &= m.TEST_EQUALS( op, Rotation<3>(PI/2, 1, 0) );

    // view-up aponta para o eixo y no sentido negativo.
    op = AxisAlignment( {0, 0, 1}, {0, -1, 0} );
    b &= m.TEST_EQUALS( op, Rotation<3>(PI/2, 0, 1) );

    // front apontando para eixo y e view-up para z.
    LinearOperator<3> ex = Rotation<3>(PI/2, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 1, 2 ) );
    op = AxisAlignment( {0, 1, 0}, {0, 0, 1} );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para eixo y no sentido contrário e view-up para z.
    ex = Rotation<3>(PI/2, 2, 0 );
    ex.backComposeWith( Rotation<3>(PI/2, 2, 1 ) );
    op = AxisAlignment( {0, -1, 0}, {0, 0, 1} );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para eixo y e view-up para z no sentido contrário
    ex = Rotation<3>(PI/2, 0, 2 );
    ex.backComposeWith( Rotation<3>(PI/2, 1, 2 ) );
    op = AxisAlignment( {0, 1, 0}, {0, 0, -1} );
    b &= m.TEST_EQUALS( op, ex );

    // front apontando para eixo y e view-up para z, ambos no sentido contrário
    ex = Rotation<3>(PI/2, 0, 2 );
    ex.backComposeWith( Rotation<3>(PI/2, 2, 1 ) );
    op = AxisAlignment( {0, -1, 0}, {0, 0, -1} );
    b &= m.TEST_EQUALS( op, ex );

    // front e view-up nas direções corretas, mas sentido contrário
    ex = Rotation<3>(PI, 0, 2 );
    op = AxisAlignment( {0, 0, -1}, {-1, 0, 0} );
    b &= m.TEST_EQUALS( op, ex );

    return b;
}
