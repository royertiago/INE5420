/* screenRenderer.cpp
 * Implementação de screenRenderer.h
 */

#include "render/screenRenderer.h"

void ScreenRenderer::drawLine( Math::Point<2> o, Math::Point<2> d ) {
    //Origin and Destiny
    Math::Point<2> wo = wt(o); //World-coordinates Origin point
    Math::Point<2> wd = wt(d); //World-coordinates Destiny point
    /* Agora, temos ambas as extremidades da linha a ser desenhada
     * em coordenadas da window. */

    clipper.setArea( wt.clippingArea() ); //TODO:Ineficiente.
    if( clipper.clip( wo, wd ) ) { //Isto já corta as extremidades...
        Pixel vo = vpt(wo); //Viewport-cordinates Origin point
        Pixel vd = vpt(wd); //Viewport-cordinates Origin point
        screen.paint( vo, vd );
    }
}
