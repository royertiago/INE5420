/* displayFile.cpp
 * Implementação de displayFile.h */

#include "displayFile.h"

#include "renderer.h"
#include "geometric/geometricObject.h"

void DisplayFile::draw( Renderer * renderer ) {
    for( GeometricObject * object : objects )
        object->draw( renderer );
}

DisplayFile::~DisplayFile() {
    for( GeometricObject * object : objects )
        delete object;
}
