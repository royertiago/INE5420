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
#include "test/lib/testerDouble.h"

/* Teste de unidade para o LineClipper clipper.
 * precision é a quantidade de vezes que a precisão exigida será
 * superior ao epsilon de máquina. */
inline bool testLineClipper( LineClipper<2> * clipper, int precision ) {
    bool b = true;
    Test::TesterDouble d(precision);

    ClippingArea ca{10, 10, 25, 20};
    clipper->setArea( ca );

    // Exemplos dos slides do Aldo
    Math::Point<2> x{5,12};
    Math::Point<2> y{15,17};

    b &= Test::TEST_EQUALS( clipper->clip( x, y ), true );
    b &= d.TEST_EQUALS( x[0], 10.0 );
    b &= d.TEST_EQUALS( x[1], 14.5 );
    b &= d.TEST_EQUALS( y[0], 15.0 );
    b &= d.TEST_EQUALS( y[1], 17.0 );

    x = Math::Point<2>{5, 18};
    y = Math::Point<2>{15, 23};
    b &= Test::TEST_EQUALS( clipper->clip( x, y ), false );

    return b;
    //TODO: incrementar com mais testes.
}

#endif // LINE_CLIPPER_TEST_H
