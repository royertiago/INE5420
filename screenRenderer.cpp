/* screenRenderer.cpp
 * Implementação de screenRenderer.h
 */

#include "screenRenderer.h"
#include "math/point.h"
#include "viewportTransform.h"
#include "windowTransform.h"
#include "view/drawable.h"

void ScreenRenderer::drawLine( Math::Point<2> o, Math::Point<2> d ) {
    //Origin and Destiny
    Math::Point<2> wo = wt(o); //World-coordinates Origin point
    Math::Point<2> wd = wt(d); //World-coordinates Destiny point
    /* Agora, temos ambas as extremidades da linha a ser desenhada
     * em coordenadas da window.
     * Aqui vai o código para o clipping, em relação à clippingArea
     * de wt. */
    Pixel vo = vpt(wo); //Viewport-cordinates Origin point
    Pixel vd = vpt(wd); //Viewport-cordinates Origin point

    screen.paint( vo, vd );
}
