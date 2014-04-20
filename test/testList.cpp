/* testList.cpp
 * Implementação de testList.h
 */

#include <vector>
#include "testFunction.h"
#include "testList.h"

using Test::TestFunction;

static std::vector< TestFunction > tests;

void Test::addTest( TestFunction t ) {
    tests.push_back( t );
}

bool Test::run() {
    for( TestFunction t : tests )
        if( t() == false )
            return false;
    return true;
}
