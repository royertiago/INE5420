/* shell.h
 * Implementação de um interpretador de comandos.
 *
 * Linhas em branco são ignoradas.
 */
#ifndef SHELL_H
#define SHELL_H

#include <map>
#include <string>
#include "command/commandInterpreter.h"

class Shell : public CommandInterpreter {
    std::map< std::string, Command * > commands;

public:
    /* Constrói um interpretador de comandos. */
    Shell();

    Shell( const Shell& ) = delete;
    Shell( Shell&& ) = delete;
    Shell& operator=( const Shell& ) = delete;
    Shell& operator=( Shell&& ) = delete;
    // Ninguém mexe neste interpretador de comandos.

    virtual ~Shell();

    // Métodos herdados
    virtual void addCommand( std::string, Command * );
    virtual void readFrom( std::istream& );
};

#endif // SHELL_H
