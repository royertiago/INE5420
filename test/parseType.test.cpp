/* parseType.test.cpp
 * Teste de unidade para as classes de command/parseType.h */

#include "command/parseType.h"

#include <string>
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"

DECLARE_TEST( ParseTypeTest ) {
    using std::string;
    using std::istringstream;
    bool b = true;

    string data = "3.25 12 42 Wangenheim 23";
    istringstream is( data );
    
    double d = ParseType< double >::parse( is );
    b &= Test::TEST_EQUALS( d, 3.25 );

    int i = ParseType< int > ::parse( is );
    b &= Test::TEST_EQUALS( i, 12 );

    double e = ParseType< double > ::parse( is );
    b &= Test::TEST_EQUALS( e, 42.0 );

    string s = ParseType< string >::parse( is );
    b &= Test::TEST_EQUALS( s.c_str(), "Wangenheim" );

    string t = ParseType< string >::parse( is );
    b &= Test::TEST_EQUALS( t.c_str(), "23" );

    return b;
}
