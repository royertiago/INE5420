/* parseType.h
 * Classe que faz o parsing de um tipo específico.
 */
#ifndef PARSE_TYPE_H
#define PARSE_TYPE_H

#include <sstream>

template< typename T >
struct ParseType {
    static T parse( std::istringstream& is ) {
        T r;
        is >> r;
        return r;
    }
};

#endif // PARSE_TYPE_H
