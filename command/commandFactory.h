/* commandFactory.h
 * Namespace que encapsula uma fábrica de comandos.
 */
#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "command/functionalCommand.h"

namespace CommandFactory {

    /* Constrói um FunctionalCommand a partir da função passada.
     * O compilador é capaz de deduzir o tipo da função a partir dos
     * argumentos; entretanto, esta função não cria comandos a partir
     * de objetos funcionais. */
    template< typename ... Format >
    Command * makeFunctional( void (*)( Format... ) );

    /* Constrói um FunctionalCommand a partir do objeto funcional
     * passado. É necessário explicitar a formatação dos parâmetros
     * que chamarâo a função. */
    template< typename ... Format, typename Functor >
    Command * makeFunctional( Functor f );


// Implementação

template< typename ... Format >
Command * makeFunctional( void (* f)( Format... ) ) {
    return new FunctionalCommand< void(*)( Format... ), Format... >( f );
}

template< typename ... Format, typename Functor >
Command * makeFunctional( Functor f ) {
    return new FunctionalCommand< Functor, Format... >( f );
}

} // namespace CommandFactory

#endif // COMMAND_FACTORY_H
