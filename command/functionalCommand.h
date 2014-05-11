/* functionalCommand.h
 * Tipo de comando que faz o parsing de uma string, conforme uma
 * formatação especificada, e executa uma função cujos argumentos
 * correspondem aos elementos obtidos na formatação.
 *
 * Por exemplo: se a função passada for
 *  double printSqr( double d ) {
 *      printf( "%lf\n", d * d );
 *  }
 * e o formato <double>, ao ler uma string do tipo "2.72", esta
 * classe executa a função printSqr passando como argumento 2.72.
 */
#ifndef FUNCTIONAL_COMMAND_H
#define FUNCTIONAL_COMMAND_H

#include "command/command.h"
#include "command/tupleCall.h"
#include "command/parseTuple.h"

template< typename Function, typename ... Format >
class FunctionalCommand : public Command {
    Function f;

public:
    /* f deve ser uma função ou objeto funcional que possui a seguinte
     * assinatura:
     * void f( Format... ). */
    FunctionalCommand( Function f );

    FunctionalCommand( const FunctionalCommand& ) = default;
    FunctionalCommand( FunctionalCommand&& ) = default;
    FunctionalCommand& operator=( const FunctionalCommand& ) = default;
    FunctionalCommand& operator=( FunctionalCommand&& ) = default;
    ~FunctionalCommand() = default;
    
    // Métodos herdados
    virtual void interpret( std::istringstream& );
    virtual void setParent( CommandInterpreter * c );
};

// Implementação

template< typename Function, typename ... Format >
FunctionalCommand< Function, Format... >::FunctionalCommand( Function f ) :
    f( f )
{}

template< typename Function, typename ... Format >
void FunctionalCommand< Function, Format... >::interpret( 
        std::istringstream& is )
{
    auto tuple = parseTuple< Format... >( is );
    tupleCall( f, tuple );
}

template< typename Function, typename ... Format >
void FunctionalCommand< Function, Format... >::setParent( CommandInterpreter* )
{
    /* Esta classe não depende da existência de um interpretador de comandos
     * para realizar suas funções. */
}

#endif // FUNCTIONAL_COMMAND_H
