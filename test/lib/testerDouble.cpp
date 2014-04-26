/* testerDouble.cpp
 * Implementação de testerDouble.h
 */
#include <cstdio>
#include <limits>
#include <cmath>

#include "testerDouble.h"

namespace Test {
    using std::printf;
    using std::fabs;

    TesterDouble::TesterDouble( double epsilon ) :
        epsilon( epsilon )
    {}

    TesterDouble::TesterDouble( int i ) :
        TesterDouble( i * std::numeric_limits<double>::epsilon() )
    {}

    TesterDouble::TesterDouble() :
        TesterDouble( 1 )
    {}

    void TesterDouble::setEpsilon( double epsilon ) {
        this->epsilon = epsilon;
    }

    bool TesterDouble::testEquals( double actualValue, double expectedValue,
            const char * lineText, int lineNumber )
    {
        if( fabs(actualValue - expectedValue) < epsilon )
            return true;

        printf( "%s\nat line %i - "
                "Value: %lf - Expected: %lf\n"
                "The value is within %le of expected. Epsilon is %le\n\n",
                lineText, lineNumber,
                actualValue, expectedValue,
                fabs(actualValue - expectedValue), epsilon);
        return false;
    }

} // namespace Test
