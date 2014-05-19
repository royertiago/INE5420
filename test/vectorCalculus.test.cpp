/* vectorCalculus.test.cpp
 * Testes de funções que fazem contas com vetores.
 */

#include "math/vector.h"
#include "math/constant.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerDouble.h"

DECLARE_TEST( VectorCalculusTest ) {
    bool b = true;
    Test::TesterDouble d;
    using namespace Math;

    // Eixos coordenados
    b &= d.TEST_EQUALS( vectorAngle<3>({0, 0, 1}, {1, 0, 0}), PI/2 );
    b &= d.TEST_EQUALS( vectorAngle<3>({0, 1, 0}, {1, 0, 0}), PI/2 );
    b &= d.TEST_EQUALS( vectorAngle<3>({0, 0, 1}, {0, 1, 0}), PI/2 );
    b &= d.TEST_EQUALS( vectorAngle<3>({1, 0, 0}, {0, 1, 0}), PI/2 );
    b &= d.TEST_EQUALS( vectorAngle<3>({0, 1, 0}, {0, 0, 1}), PI/2 );
    b &= d.TEST_EQUALS( vectorAngle<3>({1, 0, 0}, {0, 0, 1}), PI/2 );

    // Vetores opostos
    b &= d.TEST_EQUALS( vectorAngle<3>({0, 0, 1}, {0, 0, -1}), PI );
    b &= d.TEST_EQUALS( vectorAngle<3>({0, 1, 0}, {0, -1, 0}), PI );
    b &= d.TEST_EQUALS( vectorAngle<3>({1, 0, 0}, {-1, 0, 0}), PI );

    return b;
}
