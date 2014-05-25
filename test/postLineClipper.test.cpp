/* postLineClipper.test.cpp
 * Teste de unidade para o clipping de linhas.
 */

#include "render/clipping/cohenSutherland.h"
#include "render/clipping/lineClipper.h"
#include "render/projection/projectedPoint.h"
#include "test/lib/test.h"

DECLARE_TEST( PostLineClipperTest ) {
    bool b = true;
    Test::TesterDouble d;
    
    PostLineClipper clipper = &CohenSutherland;
    
    ProjectedPoint r, s;
    
    // Reta inteiramente dentro da área de clipping
    r = {-0.5, -0.5};
    s = {0.5, 0.5};
    b &= d.TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -0.5 );
    b &= d.TEST_EQUALS( r.y, -0.5 );
    b &= d.TEST_EQUALS( s.x, 0.5 );
    b &= d.TEST_EQUALS( s.y, 0.5 );
       
    /* Reta vertical parcialmente dentro da área de clipping,
     * com ambos os pontos fora da área de clipping. */
    r = {0.5, -1.5};
    s = {0.5, 1.5};
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, 0.5 );
    b &= d.TEST_EQUALS( r.y, -1.0 );
    b &= d.TEST_EQUALS( s.x, 0.5 );
    b &= d.TEST_EQUALS( s.y, 1.0 );

    /* Reta horizontal parcialmente dentro da área de clipping,
     * com ambos os pontos fora da área de clipping. */
    r = {-1.5, 0.5};
    s = {1.5, 0.5};
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -1.0 );
    b &= d.TEST_EQUALS( r.y, 0.5 );
    b &= d.TEST_EQUALS( s.x, 1.0 );
    b &= d.TEST_EQUALS( s.y, 0.5 );

    /* Reta com um ponto dentro da área de clipping e um a sudoeste,
     * com interseção no vértice da área de clipping. */
    r = {-1.5, -1.5};
    s = {0.5, 0.5};
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -1.0 );
    b &= d.TEST_EQUALS( r.y, -1.0 );
    b &= d.TEST_EQUALS( s.x, 0.5 );
    b &= d.TEST_EQUALS( s.y, 0.5 );

    /* Reta com um ponto dentro da área de clipping e um a sudeste,
     * com interseção no vértice da área de clipping. */
    r = {1.5, -1.5};
    s = {-0.5, 0.5};
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, 1.0 );
    b &= d.TEST_EQUALS( r.y, -1.0 );
    b &= d.TEST_EQUALS( s.x, -0.5 );
    b &= d.TEST_EQUALS( s.y, 0.5 );
    
    /* Reta com um ponto dentro da área de clipping e um a noroeste,
     * com interseção no vértice da área de clipping. */
    r = {-1.5, 1.5};
    s = {0.5, -0.5};
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -1.0 );
    b &= d.TEST_EQUALS( r.y, 1.0 );
    b &= d.TEST_EQUALS( s.x, 0.5 );
    b &= d.TEST_EQUALS( s.y, -0.5 );
    
    /* Reta com um ponto dentro da área de clipping e um a nordeste,
     * com interseção no vértice da área de clipping. */
    r = {1.5, 1.5};
    s = {0.5, 0.5};
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, 1.0 );
    b &= d.TEST_EQUALS( r.y, 1.0 );
    b &= d.TEST_EQUALS( s.x, 0.5 );
    b &= d.TEST_EQUALS( s.y, 0.5 );

    /* Reta inclinada parcialmente dentro da área de clipping,
     * com ambos os pontos fora. */
    r = {-3.0, -0.3};
    s = {2, 0.8};
    // y = 0.22x + 0.36
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -1.0 );
    b &= d.TEST_EQUALS( r.y, (0.7)/(5.0) );
    b &= d.TEST_EQUALS( s.x, 1.0 );
    b &= d.TEST_EQUALS( s.y, (2.9)/(5.0) );

    /* Reta inclinada parcialmente dentro da área de clipping,
     * com ambos os pontos fora. */
    r = {1.1, 0.4};     
    s = {0.3, 1.2};
    // y = -x + 1.5
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, 1.0 );
    b &= d.TEST_EQUALS( r.y, 0.5 );
    b &= d.TEST_EQUALS( s.x, 0.5 );
    b &= d.TEST_EQUALS( s.y, 1.0 );

    /* Reta inclinada parcialmente dentro da área de clipping,
     * com um ponto a noroeste e outro a leste da área de clipping */
    r = {-1.2, 1.2};
    s = {1.2, 0.6};
    // y = -0.25x + 0.9
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -0.4 );
    b &= d.TEST_EQUALS( r.y, 1.0 );
    b &= d.TEST_EQUALS( s.x, 1.0 );
    b &= d.TEST_EQUALS( s.y, 0.65 );

    /* Reta inclinada parcialmente dentro da área de clipping,
     * com um ponto a sudoeste e outro a nordeste da área de clipping */
    r = {-1.2, -1.2};
    s = {1.2, 1.5};
    // y = 1.125x + 0.15
    b &= Test::TEST_EQUALS( clipper( r, s ), true );
    b &= d.TEST_EQUALS( r.x, -1.0 );
    b &= d.TEST_EQUALS( r.y, -0.975 );
    b &= d.TEST_EQUALS( s.x, (0.85)/(1.125) );
    b &= d.TEST_EQUALS( s.y, 1.0 );

    return b;
}
