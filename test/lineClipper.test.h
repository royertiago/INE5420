/* lineClipper.test.h
 * Define uma função que executa um teste de unidade num
 * lineClipper.
 *
 * Para usá-la, declare uma função como um teste e chame
 * esta função de dentro dela.
 */
#ifndef LINE_CLIPPER_TEST_H
#define LINE_CLIPPER_TEST_H

#include "render/clipping/lineClipper.h"
#include "render/clipping/clippingArea.h"
#include "math/point.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"
#include "test/lib/testerDouble.h"

/* Teste de unidade para o LineClipper clipper.
 * precision é a quantidade de vezes que a precisão exigida será
 * superior ao epsilon de máquina. */
inline bool testLineClipper( LineClipper<2> * clipper, int precision ) {
    bool b = true;
    Test::TesterDouble d(precision);

    ClippingArea ca = {10, 10, 25, 20};
    clipper->setArea( ca );

    Math::Point<2> x{5,12};
    Math::Point<2> y{15,17};

    // Reta parcialmente dentro da área de clipping
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), true );
    b &= d.TEST_EQUALS( x[0], 10.0 );
    b &= d.TEST_EQUALS( x[1], 14.5 );
    b &= d.TEST_EQUALS( y[0], 15.0 );
    b &= d.TEST_EQUALS( y[1], 17.0 );

    // Reta inteiramente dentro da área de clipping
    x = Math::Point<2>{12, 12};
    y = Math::Point<2>{17, 17};
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), true );
    b &= d.TEST_EQUALS( x[0], 12.0 );
    b &= d.TEST_EQUALS( x[1], 12.0 );
    b &= d.TEST_EQUALS( y[0], 17.0 );
    b &= d.TEST_EQUALS( y[1], 17.0 );

    // Reta completamente fora da área de clipping, a sudoeste.
    x = Math::Point<2>{5, 5};
    y = Math::Point<2>{5, 8};
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), false );

    // Reta completamente fora da área de clipping, ao sul.
    x = Math::Point<2>{5, 5};
    y = Math::Point<2>{5, 35};
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), false );

    /* Reta parcialmente dentro da área de clipping, com um ponto
     * a sudoeste e um a nordeste da área de clipping. */
    x = Math::Point<2>{0, 0};
    y = Math::Point<2>{30, 30};
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), true );
    b &= d.TEST_EQUALS( x[0], 10.0 );
    b &= d.TEST_EQUALS( x[1], 10.0 );
    b &= d.TEST_EQUALS( y[0], 20.0 );
    b &= d.TEST_EQUALS( y[1], 20.0 );

    /* Reta totalmente fora da área de clipping, mas com um ponto
     * a sudoeste e um a nordeste da área de clipping. */
    x = Math::Point<2>{-40, 0};
    y = Math::Point<2>{30, 70};
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), false );

    return b;
}

#endif // LINE_CLIPPER_TEST_H
