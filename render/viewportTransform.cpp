/* vieportTransform.cpp
 * Implementação de viewportTransform.h */

#include "render/viewportTransform.h"

Pixel ViewportTransform::transform( Math::Point<2> p ) const {
    Pixel r; // Valor de retorno
    double xratio = (p[0] - ca.xmin)/(ca.xmax - ca.xmin);
    r.x = vp.xmin + xratio * (vp.xmax - vp.xmin);

    double yratio = (p[1] - ca.ymin)/(ca.ymax - ca.ymin);
    r.y = vp.ymin + (1 - yratio) * (vp.ymax - vp.ymin);
    return r;
}

Math::Point<2> ViewportTransform::reverseTransform( Pixel p ) const {
    Math::Point<2> r; // Valor de retorno
    double xratio = double(p.x - vp.xmin) /
                    double(vp.xmax - vp.xmin);
    r[0] = ca.xmin + xratio * (ca.xmax - ca.xmin);

    double yratio = double(p.y - vp.ymin) /
                    double(vp.ymax - vp.ymin);
    r[1] = ca.ymin + yratio * (ca.ymax - ca.ymin);
    return r;
}
