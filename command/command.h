/* command.h
 * Interface que representa um comando genérico.
 * 
 * Comandos interpretam o conteúdo de istringstreams para executar
 * suas funções. */
#ifndef COMMAND_H
#define COMMAND_H

#include <sstream>
class CommandInterpreter;   

class Command {
public:
    /* Interpreta o comando passado. A string passada não conterá
     * o nome inicial do comando; por exemplo, um comando
     *  load meuArquivoFofinho
     * seria passado para o comando identificado por "load" apenas
     * como " meuArquivoFofinho". */
    virtual void interpret( std::istringstream& ) = 0;

    /* Informa o CommandInterpreter que contêm este comando. */
    virtual void setParent( CommandInterpreter * ) = 0;

    virtual ~Command() = default;
};

#endif // COMMAND_H
