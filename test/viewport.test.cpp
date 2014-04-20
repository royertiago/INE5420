/* Teste de unidade de view/viewport.h. */

#include <cstdio>
using std::printf;

#include "view/viewport.h"
#include "registerTest.h"

bool ViewportTest() {
    Viewport v{5, 0, 10, 20};

    if( v.area() != 100 ) {
        printf( "Viewport failed test.\n" );
        return false;
    }

    return true;
}

REGISTER_TEST( ViewportTest )
