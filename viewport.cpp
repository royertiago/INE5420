/* viewport.cpp
 * Implementação de viewport.h
 */

#include "viewport.h"
#include "drawable.h"

Viewport Viewport::generateViewport( Drawable * d ) {
    return Viewport{ 0, d->width(), 0, d->height() };
}
