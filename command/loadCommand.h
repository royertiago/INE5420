/* loadCommand.h
 * Comando que ordena o interpretador principal a ler 
 * informações de arquivos.
 */
#ifndef LOAD_COMMAND_H
#define LOAD_COMMAND_H

#include "command.h"
class CommandInterpreter;

class LoadCommand : public Command {
    CommandInterpreter * shell;

public:
    LoadCommand() = default;
    LoadCommand( const LoadCommand& ) = default;
    LoadCommand( LoadCommand&& ) = default;
    LoadCommand& operator=( const LoadCommand& ) = default;
    LoadCommand& operator=( LoadCommand&& ) = default;

    // Métodos herdados
    virtual void setParent( CommandInterpreter * );
    virtual void interpret( std::istringstream& );
};

#endif // LOAD_COMMAND_H
