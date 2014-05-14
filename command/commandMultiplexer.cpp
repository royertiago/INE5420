/* commandMultiplexer.cpp
 * Implementação de commandMultiplexer.h
 */

#include <utility>
#include "commandMultiplexer.h"

CommandMultiplexer::~CommandMultiplexer() {
    for( auto& it : commands )
        delete it.second;
}

void CommandMultiplexer::setParent( CommandInterpreter * i ) {
    parent = i;
}

void CommandMultiplexer::interpret( std::istringstream& is ) {
    std::string cmd;
    is >> cmd;
    commands[cmd]->interpret( is );
}

void CommandMultiplexer::addCommand( Command * cmd, std::string name ) {
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

void CommandMultiplexer::readFrom( std::istream& is ) {
    parent->readFrom( is );
}
