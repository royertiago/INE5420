/* tupleCall.h
 * Função que toma uma função e uma tupla, e chama a função passando
 * como argumento os valores da tupla. */
#ifndef TUPLE_CALL_H
#define TUPLE_CALL_H

#include <tuple>
#include "utility/variadic.h"

template< typename Function, typename ... Args >
void tupleCall( Function f, std::tuple< Args... > t );

// Implementação
namespace {
    template< typename Function, typename ... Args, int ... Index >
    void tupleCallHelper( Function f, std::tuple< Args... > t,
            Variadic::Index< Index... > )
    {
        static_assert( sizeof...(Args) == sizeof...(Index),
                "Args e Indexes têm de ter o mesmo tamanho." );

        f( std::get<Index>( t )... );
    }
} // annonymous namespace

template< typename Function, typename ... Args >
void tupleCall( Function f, std::tuple< Args... > t ) {
    tupleCallHelper( f, t, Variadic::makeOrderedIndex< sizeof...(Args) >() );
}

#endif // TUPLE_CALL_H
