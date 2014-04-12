/* screenRenderer.cpp
 * Implementação de screenRenderer.h
 */

#include "viewportTransform.h"
#include "view/drawable.h"
#include "view/pixel.h"
#include "window.h"
#include "screenRenderer.h"

ScreenRenderer::ScreenRenderer( 
        ViewportTransform transform, Drawable * screen ) :
    transform(transform),
    screen(screen)
{}

void ScreenRenderer::drawLine( Point<2> origin, Point<2> destiny ) {
    Pixel a = transform.transform( origin );
    Pixel b = transform.transform( destiny );
    screen->paint( a, b );
}
