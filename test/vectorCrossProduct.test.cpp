/* vectorCrossProduct.test.cpp
 * Teste de unidade da função Math::CrossProduct, de math/vector.h
 */
#include "math/vector.h"

#include "test/lib/test.h"

DECLARE_TEST( VectorCrossProductTest ) {
    bool b = true;
    Test::TesterMatrix t;
    Test::TesterDouble d;

    using Math::crossProduct;
    using Math::Vector;

    Vector<3> x = {1, 0, 0};
    Vector<3> y = {0, 1, 0};
    Vector<3> z = {0, 0, 1};

    // Igualdade
    b &= t.TEST_EQUALS( crossProduct(x, y), z );
    b &= t.TEST_EQUALS( crossProduct(y, x), -z );
    b &= t.TEST_EQUALS( crossProduct(x, z), -y );
    b &= t.TEST_EQUALS( crossProduct(z, x), y );
    b &= t.TEST_EQUALS( crossProduct(y, z), x );
    b &= t.TEST_EQUALS( crossProduct(z, y), -x );

    // Ortogonalidade
    Vector<3> v = {1, 8, -7};
    Vector<3> u = {-8, 4, 0};
    b &= d.TEST_EQUALS( innerProduct( v, crossProduct( u, v ) ), 0 );
    b &= d.TEST_EQUALS( innerProduct( u, crossProduct( u, v ) ), 0 );
    b &= d.TEST_EQUALS( innerProduct( v, crossProduct( v, u ) ), 0 );
    b &= d.TEST_EQUALS( innerProduct( u, crossProduct( v, u ) ), 0 );
    b &= t.TEST_EQUALS( crossProduct(u, v), -crossProduct(v, u) );

    v = Vector<3>{7, 0, 0};
    u = Vector<3>{1, 1, 0};
    b &= d.TEST_EQUALS( innerProduct( v, crossProduct( u, v ) ), 0 );
    b &= d.TEST_EQUALS( innerProduct( u, crossProduct( u, v ) ), 0 );
    b &= d.TEST_EQUALS( innerProduct( v, crossProduct( v, u ) ), 0 );
    b &= d.TEST_EQUALS( innerProduct( u, crossProduct( v, u ) ), 0 );
    b &= t.TEST_EQUALS( crossProduct(u, v), -crossProduct(v, u) );
    return b;
}
