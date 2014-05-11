/* parseTuple.h
 * Função que faz o parsing de uma string para uma tupla,
 * baseado nas funções do cabeçalho parseType.h */
#ifndef PARSE_TUPLE_H
#define PARSE_TUPLE_H

#include <tuple>
#include <sstream>

#include "command/parseType.h"

/* Faz o parsing da string contida na stringstream passada. */
template< typename ... Ts >
std::tuple< Ts... > parseTuple( std::istringstream& );


// Implementação

namespace {
// Classe auxiliar
    template< typename ... Ts >
    struct ParseTuple;

    template<> struct ParseTuple<> {
        static std::tuple<> parseTuple( std::istringstream& ) {
            return std::make_tuple();
        }
    };

    template< typename H, typename ... Ts >
    struct ParseTuple<H, Ts...> {
        static std::tuple<H, Ts...> parseTuple( std::istringstream& is ) {
            H h = ParseType<H>::parse( is );
            return std::tuple_cat( std::make_tuple( h ), 
                    ParseTuple<Ts...>::parseTuple( is ) );
        }
    };
} // anonymous namespace

template< typename ... Ts >
std::tuple< Ts... > parseTuple( std::istringstream& is ) {
    return ParseTuple< Ts... >::parseTuple( is );
}

#endif // PARSE_TUPLE_H
