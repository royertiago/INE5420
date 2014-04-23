/* testList.cpp
 * Implementação de testList.h
 */

#include <vector>
#include <cstdio>
#include "testList.h"

namespace Test {

using std::printf;

struct TestData {
    TestFunction test;
    const char * name;
    const char * file;
};

/* Pequena gambiarra.
 * O padrão do C++ garante que o vetor interno é inicializado
 * antes da primeira execução do "return" na segunda linha. */
static std::vector< TestData >& tests() {
    static std::vector< TestData > tests;
    return tests;
}

void addTest( TestFunction t, const char * n, const char * f ) {
    tests().push_back( {t, n, f} );
}

bool run() {
    for( TestData t : tests() )
        if( t.test() == false ) {
            printf( "Test %s at file %s failed.\n", t.name, t.file );
            return false;
        }

    printf( "Number of tests: %i.\n", (int) tests().size() );
    return true;
}

} // namespace Test
