/* commandInterpreter.h
 * Interface para objecots capazes de ler e comandos de istreams 
 * específicas, redirecionando estes comandos para os objetos
 * registrados.
 */
#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>
#include "command/command.h"

class CommandInterpreter {
public:
    /* Adiciona um comando à lista.
     * O objeto assume controle sobre o ponteiro passado;
     * este objeto passa a ser o "pai" do comando.
     *
     * name é a parte do comando que será usado para diferenciá-lo
     * dos outros; por exemplo, um comando
     *  load meu_arquivo_fofinho
     * seria adicionado com o nome "load". name não deve conter 
     * espaços em branco.
     *
     * Caso já exista um comando com o nome escolhido, o comando
     * anterior será deletado. */
    virtual void addCommand( std::string name, Command * ) = 0;

    /* Lê comandos da istream passada, até chegar no fim do arquivo.
     *
     * Comandos estão separados por linhas; uma linha que não esteja
     * em branco corresponde a um comando.
     *
     * Caso este método seja chamado durante a leitura da istream 
     * atual, esta leitura deve ser interrompida e a da istream passada 
     * iniciada. Isto permite que arquivos "incluam" outros arquivos. */
    virtual void readFrom( std::istream& ) = 0;

    virtual ~CommandInterpreter() = default;
};

#endif // COMMAND_INTERPRETER_H
