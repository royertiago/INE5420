/* commandFactory.cpp
 * Implementação das funções não-template de commandFactory.h
 */

#include "commandFactory.h"
#include "command/loadCommand.h"
#include "command/echoCommand.h"

namespace CommandFactory {

    Command * nop() {
        return makeFunctional( [](){} );
    }
    
    Command * load() {
        return new LoadCommand();
    }

    Command * echo() {
        return new EchoCommand();
    }

} // namespace CommandFactory
