/* loadCommand.cpp
 * Implementação de loadCommand.h
 */

#include <fstream>
#include <string>
#include "loadCommand.h"
#include "commandInterpreter.h"

void LoadCommand::setParent( CommandInterpreter * c ) {
    shell = c;
}

void LoadCommand::interpret( std::istringstream& is ) {
    std::string fileName;
    is >> fileName;
    std::ifstream file( fileName );
    shell->readFrom( file );
}
