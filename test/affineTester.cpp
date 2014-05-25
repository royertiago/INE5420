/* affineTester.cpp
 * Implementação de AffineTester.h
 */
#include "affineTester.h"

namespace Test {

    AffineTester::AffineTester( int i ) :
        t( i )
    {}

    void AffineTester::setEpsilon( double d ) {
        t.setEpsilon( d );
    }

} // namespace Test
