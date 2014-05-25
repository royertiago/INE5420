/* Teste de unidade de window.h */

#include "render/window2d.h"

#include "test/lib/test.h"
#include "math/constant.h"

DECLARE_TEST( Window2DTest ) {
    bool b = true;

    Window<2> w;
    b &= Test::TEST_EQUALS( w.x, 0.0 );
    b &= Test::TEST_EQUALS( w.y, 0.0 );
    b &= Test::TEST_EQUALS( w.w, 2.0 );
    b &= Test::TEST_EQUALS( w.h, 2.0 );
    b &= Test::TEST_EQUALS( w.t, 0.0 );

    w.setCenter({0.5, 0.5});
    w.setWidth( 1 );
    w.setHeight( 1 );
    b &= Test::TEST_EQUALS( w.x, 0.5 );
    b &= Test::TEST_EQUALS( w.y, 0.5 );
    b &= Test::TEST_EQUALS( w.w, 1.0 );
    b &= Test::TEST_EQUALS( w.h, 1.0 );

    w.move({0.5, 0});

    b &= Test::TEST_EQUALS( w.x, 1.0 );
    b &= Test::TEST_EQUALS( w.y, 0.5 );
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
    b &= d.TEST_EQUALS( w.y, 0.5 ); //Este não passa com epsilon de máquina.
    b &= d.TEST_EQUALS( w.w, 1.0 );
    b &= d.TEST_EQUALS( w.h, 1.0 );
    b &= d.TEST_EQUALS( w.t, 0.0 );

    //Testes de escala:
    w.vscale( 2.0 );
    w.hscale( 3.0 );
    b &= Test::TEST_EQUALS( w.h, 2.0 );
    b &= Test::TEST_EQUALS( w.w, 3.0 );
    b &= Test::TEST_EQUALS( w.area(), 6.0 );

    return b;
}
