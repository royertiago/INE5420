/* parseType.test.cpp
 * Teste de unidade para as classes de command/parseType.h */

#include "command/parseType.h"

#include <string>
#include <vector>
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"

DECLARE_TEST( ParseTypeTest ) {
    using std::string;
    using std::vector;
    using std::istringstream;
    bool b = true;

    string data = "3.25 12 42 Wangenheim 23 {-1    -2 55  } "
                  "{{1 2} {9 7 8}} {} {        }";
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

    vector<int> v = ParseType< vector<int> >::parse( is );
    b &= Test::TEST_EQUALS( v.size(), 3 );
    b &= Test::TEST_EQUALS( v[0], -1 );
    b &= Test::TEST_EQUALS( v[1], -2 );
    b &= Test::TEST_EQUALS( v[2], 55 );

    vector< vector<int> > w = ParseType<vector<vector<int>>>::parse( is );
    b &= Test::TEST_EQUALS( w.size(), 2 );
    b &= Test::TEST_EQUALS( w[0].size(), 2 );
    b &= Test::TEST_EQUALS( w[1].size(), 3 );
    b &= Test::TEST_EQUALS( w[0][0], 1 );
    b &= Test::TEST_EQUALS( w[0][1], 2 );
    b &= Test::TEST_EQUALS( w[1][0], 9 );
    b &= Test::TEST_EQUALS( w[1][1], 7 );
    b &= Test::TEST_EQUALS( w[1][2], 8 );

    w = ParseType<vector<vector<int>>>::parse( is );
    b &= Test::TEST_EQUALS( w.size(), 0 );

    w = ParseType<vector<vector<int>>>::parse( is );
    b &= Test::TEST_EQUALS( w.size(), 0 );

    return b;
}
