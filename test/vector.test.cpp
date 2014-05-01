/* vector.test.cpp
 * Teste de unidade das funcionalidades da classe Matrix
 * que estão disponíveis apenas para vector. 
 *
 * Note que algumas das funcionalidades testadas são da
 * classe MatrixLine.*/

#include "math/vector.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"

DECLARE_TEST( VectorTest ) {
    bool b = true;

    Math::Vector<2> vec{1.0, 2.0};
    b &= Test::TEST_EQUALS( vec[0], 1.0 );
    b &= Test::TEST_EQUALS( vec[1], 2.0 );

    vec[0] = vec[1] = 3.0;
    b &= Test::TEST_EQUALS( vec[0], 3.0 );
    b &= Test::TEST_EQUALS( vec[1], 3.0 );

    vec[0] = 1 + (vec[1] = 2.5);
    b &= Test::TEST_EQUALS( vec[0], 3.5 );
    b &= Test::TEST_EQUALS( vec[1], 2.5 );
    b &= Test::TEST_EQUALS( vec[0][0], 3.5 );
    b &= Test::TEST_EQUALS( vec[1][0], 2.5 );
    
    vec[1] /= 4;
    b &= Test::TEST_EQUALS( vec[1], 0.625 );

    double d = vec[1];
    b &= Test::TEST_EQUALS( d, 0.625 );

    vec[0] = d = vec[1] = 4.0;
    b &= Test::TEST_EQUALS( vec[0], 4.0 );
    b &= Test::TEST_EQUALS( vec[1], 4.0 );
    b &= Test::TEST_EQUALS( d, 4.0 );

    Math::Vector<3> u = {10.0, 11.0};
    b &= Test::TEST_EQUALS( u[0], 10.0 );
    b &= Test::TEST_EQUALS( u[1], 11.0 );
    b &= Test::TEST_EQUALS( u[2], 1.0 );

    return b;
}
