/* testEquals.cpp
 * Implementação de testEquals.h
 */
#include <cstdio>
#include "testEquals.h"

namespace Test {
    using std::printf;

    bool testEquals( int actualValue, int expectedValue,
            const char * lineText, int lineNumber )
    {
        if( actualValue == expectedValue )
            return true;

        printf( "%s\nat line %i - "
                "Actual: %i - Expected: %i\n\n",
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
                "Actual: %lf - Expected: %lf\n\n",
                lineText, lineNumber,
                actualValue, expectedValue );
        return false;
    }

    bool testEquals( bool actualValue, bool expectedValue,
            const char * lineText, int lineNumber )
    {
        if( actualValue == expectedValue )
            return true;

        printf( "%s\nat line %i - "
                "Actual: %s - Expected: %s\n\n",
                lineText, lineNumber,
                actualValue ? "true":"false",
                expectedValue ? "true":"false" );
        return false;
    }

    bool testEquals( const char * actualValue, const char * expectedValue,
            const char * lineText, int lineNumber )
    {
        int i;
        for( i = 0; expectedValue[i] != '\0'; ++i )
            if( expectedValue[i] != actualValue[i] ) {
                printf( "%s\nat line %i - "
                        "Actual: %s - Expected: %s\n"
                        "First non-match is at %i\n\n",
                        lineText, lineNumber,
                        actualValue, expectedValue, i );
                return false;
            }
        if( actualValue[i] != '\0' ) {
            printf( "%s\nat line %i - "
                    "Actual: %s - Expected: %s\n"
                    "Actual string is longer\n\n",
                    lineText, lineNumber,
                    actualValue, expectedValue );
            return false;
        }

        return true;
    }

} // namespace Test
