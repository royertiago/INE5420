/* parseVector.test.cpp
 * Teste de unidade para a especialização de parseVector.h
 */

#include "parseVector.h"

#include "math/vector.h"
#include "test/lib/test.h"

DECLARE_TEST( ParseVectorTest ) {
    using std::string;
    using std::istringstream;
    bool b = true;
    Test::TesterMatrix t;

    string data = "{1 8 9.25} {-2.5  -9   } {999} {  89  .75  }";
    istringstream is( data );

    Math::Vector<3> v = ParseType<Math::Vector<3>>::parse( is );
    b &= t.TEST_EQUALS( v, (Math::Vector<3>{1, 8, 9.25}) );

    Math::Vector<3> w = ParseType<Math::Vector<3>>::parse( is );
    b &= t.TEST_EQUALS( w, (Math::Vector<3>{-2.5, -9, 0}) );

    Math::Vector<1> x = ParseType<Math::Vector<1>>::parse( is );
    b &= t.TEST_EQUALS( x, (Math::Vector<1>{999}) );

    Math::Vector<2> y = ParseType<Math::Vector<2>>::parse( is );
    b &= t.TEST_EQUALS( y, (Math::Vector<2>{89, .75}) );

    return b;
}
