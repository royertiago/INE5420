/* window.cpp
 * Implementação de window.h
 */

#include "window.h"
#include "clippingArea.h"

Window::Window( const ClippingArea& ca ) :
    x( (ca.xmax - ca.xmin)/2 ),
    y( (ca.ymax - ca.ymin)/2 ),
    w(  ca.xmax - ca.xmin ),
    h(  ca.ymax - ca.ymin ),
    t( 0 )
{}
