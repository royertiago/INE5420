/* shell.cpp
 * Implementação de shell.h
 */

#include <utility> // std::make_pair
#include <stdexcept>

#include "shell.h"
#include "commandFactory.h"

Shell::Shell() {
    addCommand( "", CommandFactory::nop() );
}

Shell::~Shell() {
    for( auto& it : commands )
        delete it.second;
}

void Shell::addCommand( std::string name, Command * cmd ) {
    auto pair = commands.insert( std::make_pair( name, cmd ) );
    // pair é um par <iterador, bool>

    cmd->setParent( this );

    /* Se a inserção ocorreu corretamente (isto é, não havia outro
     * par chave-valor com o nome escolhido, pair.second é true. */
    if( pair.second )
        return;

    /* Senão, pair.first aponta para um par<string, Command*>.
     * substituiremos pair.first->second por cmd. */
    delete pair.first->second;
    pair.first->second = cmd;
}

void Shell::readFrom( std::istream& is ) {
    while( is.good() ) {
        std::string str;
        std::getline( is, str );
        std::istringstream iss( str );
        std::string cmd;
        iss >> cmd;

        try {
            commands[cmd]->interpret( iss );
        } catch( std::runtime_error& ex ) {
            printf( "Runtime exception: %s\nParsing remaining commands...\n",
                    ex.what() );
        }

    }
}
