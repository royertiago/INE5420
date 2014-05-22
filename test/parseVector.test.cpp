/* parseVector.test.cpp
 * Teste de unidade para a especialização de parseVector.h
 */

#include "parseVector.h"

#include "math/vector.h"
#include "math/point.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testerMatrix.h"
#include "test/lib/testMacro.h"

DECLARE_TEST( ParseVectorTest ) {
    using std::string;
    using std::istringstream;
    bool b = true;
    Test::TesterMatrix t;

    string data = "{1 8 9} {-2  -9   } {999} {  89  85  }";
    istringstream is( data );

    Math::Vector<3> v = ParseType<Math::Vector<3>>::parse( is );
    b &= t.TEST_EQUALS( v, (Math::Vector<3>{1, 8, 9}) );

    Math::Vector<2> w = ParseType<Math::Vector<3>>::parse( is );
    b &= t.TEST_EQUALS( w, (Math::Vector<2>{-2, -9}) );

    Math::Point<1> x = ParseType<Math::Point<1>>::parse( is );
    b &= t.TEST_EQUALS( x, (Math::Point<1>{999}) );

    Math::Point<2> y = ParseType<Math::Point<2>>::parse( is );
    b &= t.TEST_EQUALS( y, (Math::Point<2>{89, 85}) );

    data = "{0.25 0.5} {0.0 1.0} {0.75 0.5} {0.0 -1.0}";
    istringstream js( data );

    Math::Point<3> p = ParseType<Math::Point<3>>::parse( js );
    b &= t.TEST_EQUALS( p, (Math::Point<3>{0.25, 0.5, 0}) );

    Math::Vector<3> u = ParseType<Math::Vector<3>>::parse( js );
    b &= t.TEST_EQUALS( u, (Math::Vector<3>{0.0, 1.0, 1}) );
    /* Note que u[2] == 3, devido à interação desnecessariamente
     * complexa entre vetor e ponto. */

    Math::Point<3> q = ParseType<Math::Point<3>>::parse( js );
    b &= t.TEST_EQUALS( q, (Math::Point<3>{0.75, 0.5, 0}) );

    Math::Vector<3> z = ParseType<Math::Vector<3>>::parse( js );
    b &= t.TEST_EQUALS( z, (Math::Vector<3>{0.0, -1.0, 1}) );
    return b;
}
