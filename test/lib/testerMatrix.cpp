/* testerMatrix.cpp
 * Implementação de testerMatrix.h
 */
#include <cstdio>
#include <limits>
#include <cmath>

#include "testerMatrix.h"

namespace Test {
    using std::printf;
    using std::fabs;
    
    TesterMatrix::TesterMatrix( double epsilon ) :
        epsilon( epsilon )
    {}

    TesterMatrix::TesterMatrix( int i ) :
        TesterMatrix( i * std::numeric_limits<double>::epsilon() )
    {}

    TesterMatrix::TesterMatrix() :
        TesterMatrix( 1 )
    {}

    void TesterMatrix::setEpsilon( double newEpsilon ) {
        epsilon = newEpsilon;
    }

    bool TesterMatrix::testDouble( double actual, double expected,
            const char * text, int line, int row, int column ) const
    {
        if( fabs( actual - expected ) < epsilon )
            return true;

        printf( "%s\nat line %i - value[%i][%i] - \n"
                "Actual: %le - Expected: %le\n"
                "The value is within %le of expected. Epsilon is %le\n\n",
                text, line, row, column,
                actual, expected, fabs(actual-expected), epsilon );
        return false;
    }

} // namespace Test
