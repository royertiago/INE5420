/* window3d.cpp
 * Implementação de window3d.h
 */

#include "render/window3d.h"
#include "math/affineFactory.h"

Window<3>::Window() :
    center({1, 1, 1}),
    w( 2 ),
    h( 2 ),
    d( 1 ),
    front( -center ),
    viewUp( Math::Vector<3>({-1, 2, -1}) ),
    cached( false )
{}

// Setters

void Window<3>::setCenter( Math::Vector<3> p ) {
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

void Window<3>::setDistance( double D ) {
    d = D;
    cached = false;
}

void Window<3>::setFront( Math::Vector<3> v ) {
    front = v;
    cached = false;
}

void Window<3>::setUp( Math::Vector<3> v ) {
    viewUp = v;
    cached = false;
}

// Movimentação

void Window<3>::move( Math::Vector<3> v ) {
    center = center + v;
    cached = false;
}

void Window<3>::moveFront( double d ) {
    move( front * d / norm(front) );
}

void Window<3>::moveUp( double d ) {
    move( viewUp * d / norm(viewUp) );
}

void Window<3>::moveLeft( double d ) {
    Math::Vector<3> v = crossProduct( front, viewUp );
    move( v * d / norm(v) );
}

// Zoom

void Window<3>::vscale( double factor ) {
    h *= factor;
    cached = false;
}

void Window<3>::hscale( double factor ) {
    w *= factor;
    cached = false;
}

void Window<3>::dscale( double factor ) {
    d *= factor;
    cached = false;
}

// Rotações

void Window<3>::rotate( const Math::AffineOperator<3>& op ) {
    front = op( front );
    viewUp = op( viewUp );
    cached = false;
}

void Window<3>::rotateUp( double d ) {
    Math::Vector<3> v = crossProduct( front, viewUp );
    rotate( AffineFactory::Rotation3D( d, v ) );
}

void Window<3>::rotateLeft( double d ) {
    rotate( AffineFactory::Rotation3D( d, viewUp ) );
}

void Window<3>::rotateClockwise( double d ) {
    rotate( AffineFactory::Rotation3D( d, front ) );
}


// Métodos padrão

double Window<3>::area() const {
    return w * h;
}

Math::Vector<3> Window<3>::map( Math::Vector<3> p ) const {
    if( !cached )
        computeTransform();
    return op( p );
}

void Window<3>::computeTransform() const {
    using namespace AffineFactory;
    op = Translation<3>( -center );
    op.backComposeWith( AxisAlignment( front, viewUp ) );

    Math::Matrix<3, 3> scale = { { 2/w,   0,   0 },
                                 {   0, 2/h,   0 },
                                 {   0,   0, 1/d } };
    op.backComposeWith( scale );
    cached = true;
}
