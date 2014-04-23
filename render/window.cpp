/* window.cpp
 * Implementação de window.h
 */

#include <cmath>

#include "render/window.h"
#include "render/clipping/clippingArea.h"
#include "math/vector.h"

using std::sin;
using std::cos;

Window::Window( const ClippingArea& ca ) :
    x( (ca.xmax - ca.xmin)/2 ),
    y( (ca.ymax - ca.ymin)/2 ),
    w(  ca.xmax - ca.xmin ),
    h(  ca.ymax - ca.ymin ),
    t( 0 )
{}

void Window::moveUp( Math::Vector<2> v ) {
    x += v[0] * cos(t) - v[1] * sin(t);
    y += v[0] * sin(t) + v[1] * cos(t);
    // Para dimensões maiores devemos usar transformações lineares.
}
