/* variadic.test.cpp
 * Teste de unidade das classes de variadic.h */

#include "utility/variadic.h"

#include <type_traits>

#include "test/lib/declarationMacros.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"

DECLARE_TEST( VariadicTest ) {
    bool b = true;
    using Variadic::logical_and;
    using Variadic::logical_or;

    // Operadores lógicos

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

    /* Índices ordenados - como estas estruturas não contém 
     * membros, isto aqui é apenas um teste de compilação. */
    using Variadic::makeOrderedIndex;
    using Variadic::Index;
    static_assert( std::is_same<
                        Index<>,
                        decltype(makeOrderedIndex<0>())
            >::value, "makeOrderedIndex<0> retorna resultado errado." );
    static_assert( std::is_same<
                        Index<0>,
                        decltype(makeOrderedIndex<1>())
            >::value, "makeOrderedIndex<1> retorna resultado errado." );
    static_assert( std::is_same<
                        Index<0, 1>,
                        decltype(makeOrderedIndex<2>())
            >::value, "makeOrderedIndex<2> retorna resultado errado." );
    static_assert( std::is_same<
                        Index<0, 1, 2>,
                        decltype(makeOrderedIndex<3>())
            >::value, "makeOrderedIndex<3> retorna resultado errado." );
    static_assert( std::is_same<
                        Index<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>,
                        decltype(makeOrderedIndex<10>())
            >::value, "makeOrderedIndex<10> retorna resultado errado." );
    return b;
}
