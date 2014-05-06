/* viewport.cpp
 * Implementação de viewport.h
 */

#include "render/viewport.h"

#include "view/drawable.h"

Viewport Viewport::generateViewport( Drawable * d ) {
    return Viewport{ 0, 0, d->width(), d->height() };
}
