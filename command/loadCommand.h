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
    // Métodos herdados
    virtual void setParent( CommandInterpreter * );
    virtual void interpret( std::istringstream& );
};

#endif // LOAD_COMMAND_H
