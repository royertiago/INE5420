/* nichollLeeNicholl.test.cpp
 * Teste de unidade de render/clipping/nichollLeeNicholl.h
 */

#include "render/clipping/nichollLeeNicholl.h"
#include "render/clipping/clippingArea.h"
#include "test/lineClipper.test.h"
#include "test/lib/declarationMacros.h"

DECLARE_TEST( NichollLeeNichollTest ) {
    NichollLeeNicholl clipper( ClippingArea::normalized );
    return testLineClipper( &clipper, 10 );
}
