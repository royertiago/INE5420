/* parseType.h
 * Classes que fazem parsing de um tipo específico.
 */
#ifndef PARSE_TYPE_H
#define PARSE_TYPE_H

#include <climits>
#include <limits>
#include <sstream>
#include <vector>

/* Definição padrão; todas as especializações devem possuir
 * ao menos este método estático, com a mesma assinatura. 
 *
 * Todos os tipos primitivos podem ser lidos por este tipo. */
template< typename T >
struct ParseType {
    static T parse( std::istringstream& is ) {
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

#endif // PARSE_TYPE_H
