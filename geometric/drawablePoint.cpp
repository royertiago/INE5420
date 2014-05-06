/* drawablePoint.cpp
 * Implementação de drawablePoint.h */

#include <cmath>
using std::sqrt;
using std::sin;
using std::cos;

#include "geometric/drawablePoint.h"

#include "math/constant.h"
#include "render/renderer.h"

using Math::PI;

void DrawablePoint::draw( Renderer * renderer ) {
    double density = renderer->density();

    /* Tentaremos fazer com que o diâmetro do círculo seja em torno
     * de dez píxels.
     *
     * Um quadrado de lado 1 é mapeado para uma área que, se for quadrada,
     * terá lado sqrt(density); então, um diâmetro de 10/sqrt(density) deve
     * ser mapeado num diâmetro de 10 pixels. */
    static const double radius = 2 / sqrt(density);

    // Usaremos 12 retas para desenhar o círculo:
    double theta = 2* PI / 12;
    for( int i = 0; i < 12; i++ ) {
        renderer->drawLine(
            Math::Point<2>({ p[0] + radius * cos(i*theta),
                             p[1] + radius * sin(i*theta)}),
            Math::Point<2>({ p[0] + radius * cos((i+1)*theta), 
                             p[1] + radius * sin((i+1)*theta)})
       );
    }
}
