/* screenRenderer.h
 * Implementação de renderer.h; esta classe utiliza-se de objetos
 * Drawable para transportar para a tela os resultados da renderização.
 */
#ifndef SCREEN_RENDERER_H
#define SCREEN_RENDERER_H

#include "render/renderer.h"
#include "render/viewport.h"
#include "render/window.h"
#include "render/clipping/lineClipper.h"
#include "render/projection/projector.h"
#include "math/point.h"
#include "view/drawable.h"

template< int N >
class ScreenRenderer : public Renderer<N> {
    const Window<N>& w;
    const Viewport vp;
    Projector<N> project;
    LineClipper clip;
    Drawable& screen;

public:
    /* Constrói um renderizador que utilizará a tela screen para
     * desenhar o que lhe for ordenado, de acordo com a viewport
     * e transformada de window passadas.
     * A transformada de viewport é gerada automaticamente com base
     * na viewport passada. */
    ScreenRenderer( Viewport, const Window<N>&, Projector<N>,
            LineClipper, Drawable& );

    virtual ~ScreenRenderer() = default;

    /* Altera o tipo de projeção utilizada. */
    void setProjector( Projector<N> );
    
    // Métodos herdados:
    virtual void drawLine( Math::Point<N>, Math::Point<N> ) override;
    virtual void drawTriangle( Math::Point<N>, Math::Point<N>, 
            Math::Point<N> ) override;
    virtual double density() const override;
};

// Implementação
template< int N >
ScreenRenderer<N>::ScreenRenderer( Viewport vp, const Window<N>& w,
        Projector<N> p, LineClipper c, Drawable& s ) :
    w( w ),
    vp( vp ),
    project( p ),
    clip( c ),
    screen( s )
{}

template< int N >
void ScreenRenderer<N>::setProjector( Projector<N> p ) {
    project = p;
}

template< int N >
void ScreenRenderer<N>::drawLine( Math::Point<N> o, Math::Point<N> d ) {
    //Origin and Destiny
    Math::Point<N> wo = w.map( o ); //World-coordinates Origin point
    Math::Point<N> wd = w.map( d ); //World-coordinates Destiny point
    /* Agora, temos ambas as extremidades da linha a ser desenhada
     * em coordenadas da window. */

    ProjectedPoint po = project( wo ); //Projected Origin
    ProjectedPoint pd = project( wd ); //Projected Destiny
    /* Agora as temos em coordenadas projetadas. */

    if( clip(po, pd) ) {
        Pixel vo = vp.transform( po ); //Viewport-cordinates Origin point
        Pixel vd = vp.transform( pd ); //Viewport-cordinates Origin point
        screen.paint( vo, vd );
    }
}

template< int N >
double ScreenRenderer<N>::density() const {
    return vp.area()/w.area();
}

template< int N >
void ScreenRenderer<N>::drawTriangle( Math::Point<N>, Math::Point<N>, 
        Math::Point<N> )
{
    /* Gambiarra para que o código compile.
     * TODO: implementar este método. */
}

#endif // SCREEN_RENDERER_H
