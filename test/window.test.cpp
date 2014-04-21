/* Teste de unidade de window.h */

#include "window.h"

#include "testerDouble.h"
#include "testFunction.h"
#include "declarationMacros.h"

#include "clippingArea.h"
#include "math/constant.h"

DECLARE_TEST( WindowTest ) {
    bool b = true;

    Window w( ClippingArea::normalized );
    w.move({0.5, 0});

    b &= Test::TEST_EQUALS( w.x, 1.0 );
    b &= Test::TEST_EQUALS( w.y, 0.5 );
    b &= Test::TEST_EQUALS( w.w, 1.0 );
    b &= Test::TEST_EQUALS( w.h, 1.0 );
    b &= Test::TEST_EQUALS( w.t, 0.0 );
    /* Aqui podemos usar igualdade pois estes números são
     * representáveis por completo em double. */

    Test::TesterDouble d(2); //2 * Epsilon de máquina

    w.rotate( Math::PI/6 );
    w.moveUp( {0, 1.0} );
    w.rotate( -Math::PI/6 );
    w.moveUp( {1.0, 0} );
    w.rotate( Math::PI/3 );
    w.moveUp( {-1.0, 0} );
    w.rotate( -Math::PI/3 );
    //Agora, devemos ter voltado para o ponto inicial.

    b &= d.TEST_EQUALS( w.x, 1.0 );
    b &= d.TEST_EQUALS( w.y, 0.5 ); 
    //Este teste não passa com epsilon de máquina.

    b &= d.TEST_EQUALS( w.w, 1.0 );
    b &= d.TEST_EQUALS( w.h, 1.0 );
    b &= d.TEST_EQUALS( w.t, 0.0 );

    return b;
}
