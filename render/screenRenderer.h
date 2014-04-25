/* screenRenderer.h
 * Implementação de renderer.h; esta classe utiliza-se de objetos
 * Drawable para transportar para a tela os resultados da renderização.
 *
 * Objetos desta classe possuem referências para Drawable e
 * WindowTransform. Embora as referências para a transformada é constantes
 * (isto é, este objeto não as modificará), este objeto pode ser modificado
 * externamente, fora do controle do ScreenRenderer. 
 *
 * Esta classe depende de classes que implementem a interface LineClipper
 * para fazer clipping de linhas.
 */
#ifndef SCREEN_RENDERER_H
#define SCREEN_RENDERER_H

#include "render/renderer.h"
#include "render/viewportTransform.h"
#include "render/windowTransform.h"
#include "render/viewport.h"
#include "render/clipping/lineClipper.h"
#include "math/point.h"
#include "view/drawable.h"

class ScreenRenderer : public Renderer {
    const ViewportTransform vpt;
    const WindowTransform& wt;
    LineClipper<2>& clipper;
    Drawable& screen;

public:
    /* Constrói um renderizador que utilizará a tela screen para
     * desenhar o que lhe for ordenado, de acordo com a viewport
     * e transformada de window passadas.
     * A transformada de viewport é gerada automaticamente com base
     * na viewport passada. */
    ScreenRenderer( Viewport, const WindowTransform&, LineClipper<2>&,
            Drawable& screen );

    virtual ~ScreenRenderer() = default;
    
    // Métodos herdados:
    virtual void drawLine( Math::Point<2> origin, 
            Math::Point<2> destiny ) override;
    virtual void drawPolygon( Math::Point<2> * points, 
            int numPoints ) override;
    virtual double density() override;
};

// Implementação dos métodos mais simples
inline ScreenRenderer::ScreenRenderer( Viewport v, const WindowTransform& wt,
        LineClipper<2>& clipper, Drawable& s ) :
    vpt( v, wt.clippingArea() ),
    wt( wt ),
    clipper( clipper ),
    screen( s )
{}

inline double ScreenRenderer::density() {
    return vpt.viewport().area()/wt.window().area();
}

inline void ScreenRenderer::drawPolygon( Math::Point<2> *, int ) {
    /* Gambiarra para que o código compile.
     * TODO: implementar este método. */
}

#endif // SCREEN_RENDERER_H

