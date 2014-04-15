/* screenRenderer.h
 * Implementação de renderer.h; esta classe utiliza-se de objetos
 * Drawable para transportar para a tela os resultados da renderização.
 *
 * Objetos desta classe possuem referências para Drawable, Viewport e
 * WindowTransform. Embora as referências para transformadas são constantes
 * (isto é, este objeto não as modificará), os objetos podem ser modificados
 * externamente, fora do controle do ScreenRenderer. Objetos desta
 * classe assumirão que qualquer alteração feita nestes objetos seja
 * consistente; isto é, as transformadas devem se referir à mesma
 * área de clipping.
 */
#ifndef SCREEN_RENDERER_H
#define SCREEN_RENDERER_H

#include "renderer.h"
#include "point.h"
#include "viewportTransform.h"
#include "windowTransform.h"
#include "view/viewport.h"
#include "view/drawable.h"

class ScreenRenderer : public Renderer {
    const ViewportTransform vpt;
    const WindowTransform& wt;
    Drawable& screen; 

public:
    /* Constrói um renderizador que utilizará a tela screen para
     * desenhar o que lhe for ordenado, de acordo com o transformador
     * passado.
     * A transformada de viewport é gerada automaticamente com base
     * na viewport passada. */
    ScreenRenderer( Viewport, const WindowTransform&,
            Drawable& screen );

    virtual ~ScreenRenderer() = default;
    
    // Métodos herdados:
    virtual void drawLine( Point<2> origin, Point<2> destiny ) override;
    virtual void drawPolygon( Point<2> * points, int numPoints ) override;
    virtual double density() override;
};

// Implementação dos métodos mais simples
inline ScreenRenderer::ScreenRenderer( Viewport v, const WindowTransform& wt,
        Drawable& s ) :
    vpt( v, wt.clippingArea() ),
    wt( wt ),
    screen( s )
{}

inline double ScreenRenderer::density() {
    return vpt.viewport().area()/wt.window().area();
}

inline void ScreenRenderer::drawPolygon( Point<2> *, int ) {
    /* Gambiarra para que o código compile.
     * TODO: implementar este método. */
}

#endif // SCREEN_RENDERER_H

