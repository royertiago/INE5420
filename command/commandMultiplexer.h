/* commandMultiplexer.h
 * Classe que fica entre um grupo de comandos que e um interpretador
 * de comandos. 
 *
 * Exemplo: considere o grupo de comandos
 *  move up
 *  move left
 *  move right
 *  move down
 * Este grupo de comandos pode ser registrado num CommandMultiplexer
 * (uma função seria registrada como "up", outra como "left"...), e
 * este CommandMultiplexer registrado no interpretador de comandos
 * "oficial" como "move".
 *
 * O método readFrom redireciona para o commandInterpreter "oficial".
 *
 * Particularidade do CommandMultiplexer: adicionar um comando cujo
 * nome é "" define um comando "padrão": se nenhum comando for explicitado
 * (no exemplo acima, apenas um comando "move" seria adicionado), 
 * é este comando que será executado. Note que este comando não pode ter
 * parâmetros.
 */
#ifndef COMMAND_MULTIPLEXER_H
#define COMMAND_MULTIPLEXER_H

#include <map>
#include <string>

#include "command.h"
#include "commandInterpreter.h"

class CommandMultiplexer : public Command, public CommandInterpreter {
    std::map< std::string, Command * > commands;
    CommandInterpreter * parent;

public:
    /* Constrói um interpretador de comandos vazio. */
    CommandMultiplexer() = default;

    virtual ~CommandMultiplexer();

    // Métodos herdados de Command
    virtual void interpret( std::istringstream& ) override;
    virtual void setParent( CommandInterpreter * ) override;

    // Métodos herdados de CommandInterpreter
    virtual void addCommand( std::string, Command * ) override;
    virtual void readFrom( std::istream& ) override;
};

#endif // COMMAND_MULTIPLEXER_H
