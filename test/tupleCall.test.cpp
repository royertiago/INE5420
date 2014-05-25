/* tupleCall.test.cpp
 * Teste de unidade para a função tupleCall
 */

#include "command/tupleCall.h"

#include <tuple>
#include <vector>

#include "test/lib/test.h"

// Funções usadas neste teste
namespace {

    bool b;
    /* Todas as funções atualizarão este valor booleano para verdadeiro
     * sempre que forem chamadas corretamente */

    void f() {
        b = true;
    }
    
    void g42( int i ) {
        b = Test::TEST_EQUALS( i, 42 );
    }

    void g2( int i ) {
        b = Test::TEST_EQUALS( i, 2 );
    }

    void h( int i, int j ) {
        b = Test::TEST_EQUALS( i, 1 );
        b &= Test::TEST_EQUALS( j, 2 );
    }

    void p( int i, int j, int k ) {
        b = Test::TEST_EQUALS( i, 1 );
        b &= Test::TEST_EQUALS( j, 2 );
        b &= Test::TEST_EQUALS( k, 3 );
    }

    void q( int i, double j, double k ) {
        b = Test::TEST_EQUALS( i, 1 );
        b &= Test::TEST_EQUALS( j, 2.0 );
        b &= Test::TEST_EQUALS( k, 3.0 );
    }

    void r( double i, int j, double k ) {
        b = Test::TEST_EQUALS( i, 1.0 );
        b &= Test::TEST_EQUALS( j, 2 );
        b &= Test::TEST_EQUALS( k, 3.0 );
    }

    void t( std::vector<double> v ) {
        b = Test::TEST_EQUALS( v.size(), 2 );
        b &= Test::TEST_EQUALS( v[0], 2.0 );
        b &= Test::TEST_EQUALS( v[1], 3.0 );
    }
} // annonymous namespace

DECLARE_TEST( TupleCallTest ) {
    bool b = true;

    tupleCall( f, std::make_tuple() );
    b &= ::b;
    
    tupleCall( g42, std::make_tuple(42) );
    b &= ::b;
    
    tupleCall( g2, std::make_tuple(2) );
    b &= ::b;
    
    tupleCall( h, std::make_tuple(1, 2) );
    b &= ::b;
    
    tupleCall( p, std::make_tuple(1, 2, 3) );
    b &= ::b;
    
    tupleCall( q, std::make_tuple(1, 2.0, 3.0) );
    b &= ::b;

    tupleCall( r, std::make_tuple(1.0, 2, 3.0) );
    b &= ::b;

    tupleCall( t, std::make_tuple(std::vector<double>{2.0, 3.0}) );
    b &= ::b;

    bool alce = false;
    tupleCall( [&alce](){ alce = true; }, std::make_tuple() );
    b &= alce;

    alce = false;
    tupleCall( [&alce](int i){
            alce = Test::TEST_EQUALS( i, 2 );
            }, std::make_tuple(2) );
    b &= alce;

    return b;
}
