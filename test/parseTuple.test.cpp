/* parseTuple.test.cpp
 * Teste de unidade para a função parseTuple */

#include "command/parseTuple.h"

#include <string>
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"

DECLARE_TEST( ParseTupleTest ) {
    using std::string;
    using std::istringstream;
    using std::tuple;
    using std::get;

    bool b = true;

    istringstream is1( "3.25 12 42 Wangenheim 23" );
    auto t1 = parseTuple<double, int, double, string, string>( is1 );

    b &= Test::TEST_EQUALS( get<0>( t1 ), 3.25 );
    b &= Test::TEST_EQUALS( get<1>( t1 ), 12 );
    b &= Test::TEST_EQUALS( get<2>( t1 ), 42.0 );
    b &= Test::TEST_EQUALS( get<3>( t1 ).c_str(), "Wangenheim" );
    b &= Test::TEST_EQUALS( get<4>( t1 ).c_str(), "23" );


    istringstream is2( "move vector object1 3 5.0 Aldo" );
    auto t2 = parseTuple<string, string, string, double, double>( is2 );

    b &= Test::TEST_EQUALS( get<0>( t2 ).c_str(), "move" );
    b &= Test::TEST_EQUALS( get<1>( t2 ).c_str(), "vector" );
    b &= Test::TEST_EQUALS( get<2>( t2 ).c_str(), "object1" );
    b &= Test::TEST_EQUALS( get<3>( t2 ), 3.0 );
    b &= Test::TEST_EQUALS( get<4>( t2 ), 5.0 );

    string str;
    is2 >> str;
    b &= Test::TEST_EQUALS( str.c_str(), "Aldo" );
    // parseTuple não pode ter consumido toda a string.

    return b;
}
