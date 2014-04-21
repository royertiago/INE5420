/* testList.cpp
 * Implementação de testList.h
 */

#include <vector>
#include <cstdio>
#include "testFunction.h"
#include "testList.h"

namespace Test {

using std::printf;

struct TestData {
    TestFunction test;
    const char * name;
    const char * file;
};

static std::vector< TestData > tests;

void addTest( TestFunction t, const char * n, const char * f ) {
    tests.push_back( {t, n, f} );
}

bool run() {
    for( TestData t : tests )
        if( t.test() == false ) {
            printf( "Test %s at file %s failed.\n", t.name, t.file );
            return false;
        }
    return true;
}

} // namespace Test
