/* clippingArea.cpp
 * Implementação de clippingArea.h */

#include "clippingArea.h"

const ClippingArea ClippingArea::normalized = {0, 0, 1, 1};

void ClippingArea::move( Math::Vector<2> v ) {
    xmin += v[0];
    xmax += v[0];
    ymin += v[1];
    ymax += v[1];
}

void ClippingArea::move( double x, double y ) {
    xmin += x;
    xmax += x;
    ymin += y;
    ymax += y;
    
}

void ClippingArea::hscale( double factor ) {
    double center = (xmax + xmin)/2;
    double distance = (xmax - xmin)/2; //Distância até o centro
    xmin = center - factor*distance;
    xmax = center + factor*distance;
}

void ClippingArea::vscale( double factor ) {
    double center = (ymax + ymin)/2;
    double distance = (ymax - ymin)/2; //Distância até o centro
    ymin = center - factor*distance;
    ymax = center + factor*distance;
}
