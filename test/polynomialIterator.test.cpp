/* polynomilIterator.test.cpp
 * Teste de unidade para a classe PolynomialIterator
 */

#include "math/polynomial.h"
#include "math/polynomialIterator.h"
#include "test/lib/test.h"

DECLARE_TEST( PolynomialIteratorTest ) {
    Test::TesterDouble t;
    using Math::Polynomial;
    using Math::PolynomialIterator;
    bool b = true;

    Polynomial<double> p( std::vector<double>{2, 1} );
    PolynomialIterator<double> it = p.iterator( 0, 1 );
    b &= t.TEST_EQUALS( *it, p(0) );
    ++it;
    b &= t.TEST_EQUALS( *it, p(1) );
    ++it;
    b &= t.TEST_EQUALS( *it, p(2) );
    ++it;
    b &= t.TEST_EQUALS( *it, p(3) );
    ++it;
    b &= t.TEST_EQUALS( *it, p(4) );

    p = Polynomial<double>( std::vector<double>{50, 10, 1} );
    PolynomialIterator<double> jt = p.iterator( 0, 0.5 );
    b &= t.TEST_EQUALS( *jt, p(0) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(0.5) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(1) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(1.5) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(2.0) );
    jt.step( 1 );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(3) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(4) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(5) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(6) );
    ++jt;
    b &= t.TEST_EQUALS( *jt, p(7) );

    p = Polynomial<double>( std::vector<double>{-100, 50, -10, 2, 1} );
    PolynomialIterator<double> kt = p.iterator( -5, 0.1 );
    t.setEpsilon( 1e-6 ); //Precisão cai muito rapidamente

    int i = 0;
    for( ; kt < 5; ++i, ++kt )
        b &= t.TEST_EQUALS( *kt, p(i * 0.1 - 5) );
    kt.start( kt );
    for( ; kt < 10; ++i, ++kt )
        b &= t.TEST_EQUALS( *kt, p(i * 0.1 - 5) );

    return b;
}
