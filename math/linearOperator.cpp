/* linearOperator.cpp
 * Contém as implementações das funções estilo fábrica.
 * TODO: pôr dentro de algum escopo
 */

#include <cmath>
using std::sin;
using std::cos;

#include "linearOperator.h"
#include "math/matrix.h"
#include "math/vector.h"
#include "point.h"

using namespace Math;

LinearOperator<2> LinearFactory::make2DTranslation( Vector<2> v ) {
    return LinearOperator<2>{ {1, 0, v[0]},
             {0, 1, v[1]},
             {0, 0, 1}
           };
}

LinearOperator<2> LinearFactory::make2DScale( double d ) {
    return LinearOperator<2>{ {d, 0, 0},
                              {0, d, 0},
                              {0, 0, 1}
                            };
}

LinearOperator<2> LinearFactory::make2DRotation( double t ) {
    return LinearOperator<2>{ {cos(t), -sin(t), 0},
                              {sin(t),  cos(t), 0},
                              {     0,       0, 1},
                            };
}

LinearOperator<2> LinearFactory::make2DScale( double d, Point<2> center ) {
    Vector<2> c;
    c[0] = center[0];
    c[1] = center[1];
    LinearOperator<2> o = make2DTranslation( c );
    o.frontComposeWith( make2DScale( d ) );
    o.frontComposeWith( make2DTranslation( -c ) );
    //A ordem está "invertida" para usarmos o frontComposeWith.
    return o;
}

LinearOperator<2> LinearFactory::make2DRotation( double d, Point<2> center ) {
    Vector<2> c;
    c[0] = center[0];
    c[1] = center[1];
    LinearOperator<2> o = make2DTranslation( c );
    o.frontComposeWith( make2DRotation( d ) );
    o.frontComposeWith( make2DTranslation( -c ) );
    return o;
}
