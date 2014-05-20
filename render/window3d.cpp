/* window3d.cpp
 * Implementação de window3d.h
 */

#include "render/window3d.h"

Window<3>::Window() :
    center({2/3.0, 2/3.0, 1}),
    w( 2 ),
    h( 2 ),
    d( 1 ),
    front( -center ),
    viewUp( Math::Vector<3>({-1, 13.0/4, -3.0/2}) ),
    cached( false )
{}

void Window<3>::setCenter( Math::Point<3> p ) {
    center = p;
    cached = false;
}

void Window<3>::setWidth( double d ) {
    w = d;
    cached = false;
}

void Window<3>::setHeight( double d ) {
    h = d;
    cached = false;
}

void Window<3>::move( Math::Vector<3> v ) {
    center[0] = center[0] + v[0];
    center[1] = center[1] + v[1];
    center[2] = center[2] + v[2];
    cached = false;
}

void Window<3>::vscale( double factor ) {
    h *= factor;
    cached = false;
}

void Window<3>::hscale( double factor ) {
    w *= factor;
    cached = false;
}

void Window<3>::rotate( const Math::LinearOperator<3>& op ) {
    front = Math::Vector<3>( op(Math::Point<3>(front)) );
    viewUp = Math::Vector<3>( op(Math::Point<3>(viewUp)) );
    cached = false;
}

// Métodos padrão

double Window<3>::area() const {
    return w * h;
}

Math::Point<3> Window<3>::map( Math::Point<3> p ) const {
    if( !cached )
        computeTransform();
    return op( p );
}

void Window<3>::computeTransform() const {
    using namespace LinearFactory;
    op = Translation<3>( -center );
    op.backComposeWith( AxisAlignment( front, viewUp ) );
    Math::LinearOperator<3> scale = { { 2/w,   0,   0, 0 },
                                      {   0, 2/h,   0, 0 },
                                      {   0,   0, 1/d, 0 },
                                      {   0,   0,   0, 1 } };

    op.backComposeWith( scale );
    cached = true;
}
