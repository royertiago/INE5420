/* testFunction.cpp
 * Implementação de testFunction.h
 */
#include <cstdio>
#include "testFunction.h"

namespace Test {
    using std::printf;

    bool testEquals( int actualValue, int expectedValue,
            const char * lineText, int lineNumber )
    {
        if( actualValue == expectedValue )
            return true;

        printf( "%s\nat line %i - "
                "Value: %i - Expected: %i\n\n",
                lineText, lineNumber,
                actualValue, expectedValue );
        return false;
    }

    bool testEquals( double actualValue, double expectedValue,
            const char * lineText, int lineNumber )
    {
        if( actualValue == expectedValue )
            return true;

        printf( "%s\nat line %i - "
                "Value: %lf - Expected: %lf\n\n",
                lineText, lineNumber,
                actualValue, expectedValue );
        return false;
    }

} // namespace Test
