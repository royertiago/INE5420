/* window.cpp
 * Implementação de window.h
 */

#include <cmath>

#include "render/window.h"
#include "math/linearOperator.h"

using std::sin;
using std::cos;

Window<2>::Window() :
    x( 0 ),
    y( 0 ),
    w( 2 ),
    h( 2 ),
    t( 0 )
{}

void Window<2>::setCenter( Math::Point<2> p ) {
    x = p[0];
    y = p[1];
    cached = false;
}

void Window<2>::setWidth( double d ) {
    w = d;
    cached = false;
}

void Window<2>::setHeight( double d ) {
    h = d;
    cached = false;
}

void Window<2>::setTheta( double d ) {
    t = d;
    cached = false;
}

void Window<2>::move( Math::Vector<2> v ) {
    x += v[0];
    y += v[1];
    cached = false;
}

void Window<2>::moveUp( Math::Vector<2> v ) {
    x += v[0] * cos(t) - v[1] * sin(t);
    y += v[0] * sin(t) + v[1] * cos(t);
    cached = false;
}

void Window<2>::vscale( double factor ) {
    h *= factor;
    cached = false;
}

void Window<2>::hscale( double factor ) {
    w *= factor;
    cached = false;
}
/* Cuidado com a nomenclatura: apesar do nome hscale, quem
 * mexe na variável h é vscale. */

void Window<2>::rotate( double angle ) {
    t += angle;
    cached = false;
}

// Métodos padrão

double Window<2>::area() const {
    return w * h;
}

Math::Point<2> Window<2>::map( Math::Point<2> p ) const {
    if( !cached )
        computeTransform();
    return op( p );
}

void Window<2>::computeTransform() const {
    using namespace LinearFactory;
    op = Translation<2>( {-x, -y} );
    /* Acabamos de deslocar o centro da window para o centro do mundo.
     * Agora, usaremos as transformações com base na origem do mundo
     * para alinhar-mo-nos com o sistema de coordenadas da window.  */
    
    op.backComposeWith( Rotation<2>( -t, 0, 1 ) );
    //Agora, os eixos de ambos estão na orientação correta.

    Math::LinearOperator<2> scale = { { 2/w,   0, 0 },
                                      {   0, 2/h, 0 },
                                      {   0,   0, 1 } };

    op.backComposeWith( scale );
    cached = true;
}
