/* commandFactory.h
 * Namespace que encapsula uma fábrica de comandos.
 */
#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "command/functionalCommand.h"

namespace CommandFactory {

    /* Constrói um FunctionalCommand a partir da função passada. */
    template< typename ... Format >
    Command * makeFunctional( void (*)( Format... ) );

    /* Constrói um FunctionalCommand a partir do objeto funcional
     * passado. A formatação dos parâmetros é deduzida a partir
     * de Functor::operator(). */
    template< typename Functor >
    Command * makeFunctional( Functor f );

    /* Constrói um comando que faz nada.
     * Pode ser usado para definir comentários, por exemplo. */
    Command * nop();

    /* Constrói um comando que carrega arquivos para serem interpretados
     * pelo interpretador de comandos. */
    Command * load();

    /* Constrói um comando que ecoa todos os seus argumentos. */
    Command * echo();


// Implementação

template< typename ... Format >
Command * makeFunctional( void (* f)( Format... ) ) {
    return new FunctionalCommand< void(*)( Format... ), Format... >( f );
}

template< typename ... Format, typename Functor >
Command * makeFunctionalCommandHelper( 
        Functor f, void ( Functor::* )( Format... ) )
{
    return new FunctionalCommand< Functor, Format... >( f );
}

template< typename ... Format, typename Functor >
Command * makeFunctionalCommandHelper( 
        Functor f, void ( Functor::* )( Format... ) const )
{
    return new FunctionalCommand< Functor, Format... >( f );
}

template< typename Functor >
Command * makeFunctional( Functor f ) {
    return makeFunctionalCommandHelper( f, &Functor::operator() );
}

} // namespace CommandFactory

#endif // COMMAND_FACTORY_H
