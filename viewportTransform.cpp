/* vieportTransform.cpp
 * Implementação de viewportTransform.h */

#include "viewportTransform.h"
#include "view/pixel.h"
#include "view/viewport.h"
#include "window.h"
#include "point.h"

ViewportTransform::ViewportTransform( Viewport v, Window w ) :
    _viewport( v ),
    _window( w )
{}

Pixel ViewportTransform::transform( Point<2> p ) const {
    Pixel r; // Valor de retorno
    double xratio = (p[0] - _window.xmin)/(_window.xmax - _window.xmin);
    r.x = _viewport.xmin + xratio * (_viewport.xmax - _viewport.xmin);

    double yratio = (p[1] - _window.ymin)/(_window.ymax - _window.ymin);
    r.y = _viewport.ymin + (1 - yratio) * (_viewport.ymax - _viewport.ymin);
    return r;
}

Point<2> ViewportTransform::transform( Pixel p ) const {
    Point<2> r; // Valor de retorno
    double xratio = double(p.x - _viewport.xmin) /
                    double(_viewport.xmax - _viewport.xmin);
    r[0] = _window.xmin + xratio * (_window.xmax - _window.xmin);

    double yratio = double(p.y - _viewport.ymin) /
                    double(_viewport.ymax - _viewport.ymin);
    r[1] = _window.ymin + yratio * (_window.ymax - _window.ymin);
    return r;
}

double ViewportTransform::density() const {
    return (_viewport.xmax - _viewport.xmin) *
           (_viewport.ymax - _viewport.ymin)
        / (
           (_window.xmax - _window.xmin ) *
           (_window.ymax - _window.ymin )
          );
}
