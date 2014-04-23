/* Teste de unidade de view/viewport.h. */

#include "view/viewport.h"
#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/class/testerDrawable.h"

DECLARE_TEST( ViewportTest ) {
    bool b = true;

    // Note que estas não são operações de curto-circuito.
    b &= Test::TEST_EQUALS( Viewport({5, 0, 10, 20}).area(), 100 );

    /* TEST_EQUALS( Viewport{5, 0, 10, 20}.area(), 100 );
     * Sem os parênteses, isto dá erro de compilação: o preprocessador
     * pensa que estamos passando cinco parâmetros para a macro:
     * Viewport{5
     * 0
     * 10
     * 20}.area()
     * 100
     */

    b &= Test::TEST_EQUALS( Viewport({0, 0, 19, 23}).area(), 19*23 );

    TesterDrawable pseudoScreen(13, 29);
    Viewport vp = Viewport::generateViewport( &pseudoScreen );

    b &= Test::TEST_EQUALS( vp.xmin, 0 );
    b &= Test::TEST_EQUALS( vp.ymin, 0 );
    b &= Test::TEST_EQUALS( vp.xmax, 13 );
    b &= Test::TEST_EQUALS( vp.ymax, 29 );
    b &= Test::TEST_EQUALS( vp.area(), 13*29 );

    return b;
}
