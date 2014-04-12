/* window.cpp
 * Implementação de window.h */

#include "window.h"
#include "matrix.h"

void Window::move( Math::Vector<2> v ) {
    xmin += v(0);
    xmax += v(0);
    ymin += v(1);
    ymax += v(1);
}

void Window::move( double x, double y ) {
    xmin += x;
    xmax += x;
    ymin += y;
    ymax += y;
    
}

void Window::hscale( double factor ) {
    double center = (xmax + xmin)/2;
    double distance = (xmax - xmin)/2; //Distância até o centro
    xmin = center - factor*distance;
    xmax = center + factor*distance;
}

void Window::vscale( double factor ) {
    double center = (ymax + ymin)/2;
    double distance = (ymax - ymin)/2; //Distância até o centro
    ymin = center - factor*distance;
    ymax = center + factor*distance;
}
