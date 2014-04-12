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
    double center = (xmin + xmax)/2;
    double distance = (xmin - xmax)/2; //Distância até o centro
    xmin = center - factor*distance;
    xmax = center + factor*distance;
}

void Window::vscale( double factor ) {
    double center = (ymin + ymax)/2;
    double distance = (ymin - ymax)/2; //Distância até o centro
    ymin = center - factor*distance;
    ymax = center + factor*distance;
}
