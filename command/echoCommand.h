/* echoCommand.h
 * Comando que simplesmente ecoa tudo o que lê, exceto espaços em
 * branco iniciais.
 */
#ifndef ECHO_COMMAND_H
#define ECHO_COMMAND_H

#include "command.h"

class EchoCommand : public Command {
    // Sem membros, sem construtores
    
    // Métodos herdados
    virtual void interpret( std::istringstream& );
    virtual void setParent( CommandInterpreter * );
};

#endif // ECHO_COMMAND_H
