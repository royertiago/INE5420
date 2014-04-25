/* cohenSutherland.test.cpp
 * Teste de unidade de render/clipping/cohenSutherland.h
 */

#include "render/clipping/cohenSutherland.h"
#include "render/clipping/clippingArea.h"
#include "test/lineClipper.test.h"
#include "test/lib/declarationMacros.h"

DECLARE_TEST( CohenSutherlandTest ) {
    CohenSutherland clipper( ClippingArea::normalized );
    return testLineClipper( &clipper, 10 );
}
