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

    return b;
}
