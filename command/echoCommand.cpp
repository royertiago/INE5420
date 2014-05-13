/* echoCommand.cpp
 * Implementação de echoCommand.h
 */

#include <cstdio>
#include <sstream>
#include <string>
#include "echoCommand.h"

void EchoCommand::interpret( std::istringstream& is ) {
    std::string str;
    is >> str;
    std::printf( "%s", str.c_str() );
    // Assim, ignoramos quaisquer espaços em branco iniciais.
    
    str.clear();
    std::getline( is, str );
    std::printf( "%s\n", str.c_str() );
    /* O .clear() aí em cima é para que, caso o std::getline() não
     * leia caractere algum, o printf imprima algo vazio. */
}

void EchoCommand::setParent( CommandInterpreter * ) {
    // Não dependemos de um CommandInterpreter.
}
