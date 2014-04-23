/* variadic.test.cpp
 * Teste de unidade das classes de variadic.h */

#include "variadic.h"
#include "test/lib/testEquals.h"
#include "test/lib/declarationMacros.h"

DECLARE_TEST( VariadicTest ) {
    bool b = true;

    // "Nulários"
    b &= Test::TEST_EQUALS( logical_and<>::value, true );
    b &= Test::TEST_EQUALS( logical_or<>::value, false );

    // Unários
    b &= Test::TEST_EQUALS( logical_and<true>::value, true );
    b &= Test::TEST_EQUALS( logical_and<false>::value, false );
    b &= Test::TEST_EQUALS( logical_or<true>::value, true );
    b &= Test::TEST_EQUALS( logical_or<false>::value, false );

    // Binários
    b &= Test::TEST_EQUALS( (logical_and<true,  true >::value), true );
    b &= Test::TEST_EQUALS( (logical_and<false, true >::value), false );
    b &= Test::TEST_EQUALS( (logical_and<true,  false>::value), false );
    b &= Test::TEST_EQUALS( (logical_and<false, false>::value), false );

    b &= Test::TEST_EQUALS( (logical_or<true,  true >::value), true );
    b &= Test::TEST_EQUALS( (logical_or<false, true >::value), true );
    b &= Test::TEST_EQUALS( (logical_or<true,  false>::value), true );
    b &= Test::TEST_EQUALS( (logical_or<false, false>::value), false );

    // Alguns Quinários
    b &= Test::TEST_EQUALS( (logical_and<true, true, true, 
                true, true>::value), true );
    b &= Test::TEST_EQUALS( (logical_and<true, true, true, 
                false, true>::value), false );
    b &= Test::TEST_EQUALS( (logical_and<true, false, true, 
                true, true>::value), false );
    b &= Test::TEST_EQUALS( (logical_or<false, true, false, 
                false, true>::value), true );
    b &= Test::TEST_EQUALS( (logical_or<true, true, true, 
                true, true>::value), true );
    b &= Test::TEST_EQUALS( (logical_or<false, false, false, 
                false, false>::value), false );

    return b;
}
