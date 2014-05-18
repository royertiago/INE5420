/* parseType.h
 * Classes que fazem parsing de um tipo específico.
 */
#ifndef PARSE_TYPE_H
#define PARSE_TYPE_H

#include <limits>
#include <sstream>
#include <stdexcept>

// Tipos sobrecarregados
#include <vector>
#include <utility> //std::pair

/* Definição padrão; todas as especializações devem possuir
 * ao menos este método estático, com a mesma assinatura. 
 *
 * Todos os tipos primitivos podem ser lidos por este tipo. */
template< typename T >
struct ParseType {
    static T parse( std::istringstream& is ) {
        if( !is.good() )
            throw std::runtime_error( "Bad istringstream on ParseType" );

        T r;
        is >> r;
        return r;
    }
};

/* O formato esperado de um vector é
 *  {T T T}
 * isto é, um abre-chaves seguido de várias strings (possivelment zero,
 * nenhuma delas começadas com um fecha-chaves) que serão lidas
 * como valores do tipo T por outras versões desta classe, seguido
 * de um fecha-chaves.
 *
 * Podem haver um ou mais espaços entre o último tipo e o fecha-chaves. */
template< typename T >
struct ParseType< std::vector<T> > {
    static std::vector<T> parse( std::istringstream& is ) {
        std::vector<T> r;
        /* Pular todos os caracteres até achar '{'.
         * A função ignora o abre-chaves achado também. */
        is.ignore( std::numeric_limits<std::streamsize>::max(), '{' );
        while( is.peek() != '}' ) {
            if( std::isspace( is.peek() ) )
                is.ignore();
            else
                r.push_back( ParseType<T>::parse( is ) );
            /* Se foi encontrado um espaço, pula o caractere e continua.
             * Senão, interpreta o que quer que tenha sido lido como
             * um objeto do tipo T e adicione-o ao vetor. */
        }
        is.ignore(); // pula o '}' terminal
        return r;
    }
};

/* O formato esperado é
 *  (T U)
 */
template< typename T, typename U >
struct ParseType< std::pair<T, U> > {
    static std::pair<T, U> parse( std::istringstream& is ) {
        is.ignore( std::numeric_limits<std::streamsize>::max(), '(' );
        T t;
        is >> t;
        U u;
        is >> u;
        is.ignore( std::numeric_limits<std::streamsize>::max(), ')' );
        return std::make_pair( t, u );
    }
};
#endif // PARSE_TYPE_H
