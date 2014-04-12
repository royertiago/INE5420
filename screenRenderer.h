/* screenRenderer.h
 * Implementação de renderer.h; esta classe utiliza-se de objetos
 * Drawable para transportar para a tela os resultados da renderização.
 */
#ifndef SCREEN_RENDERER_H
#define SCREEN_RENDERER_H

#include "viewportTransform.h"
#include "view/drawable.h"
#include "view/pixel.h"
#include "window.h"
#include "renderer.h"

class ScreenRenderer : public Renderer {
    ViewportTransform transform; // Transform
    Drawable * screen; // Screen

public:
    /* Constrói um renderizador que utilizará a tela screen para
     * desenhar o que lhe for ordenado, de acordo com o transformador
     * passado.
     *
     * Esta classe não é a "proprietária" do Drawable passado; ela
     * não irá limpar o ponteiro na deleção. */
    ScreenRenderer( ViewportTransform transform, Drawable * screen );

    virtual ~ScreenRenderer() = default;
    
    // Métodos herdados:
    virtual void drawLine( Point<2> origin, Point<2> destiny ) override;

    virtual Window window() override {
        return transform.window();
    }

    virtual double density() override {
        return transform.density();
    }

    /* Retorna o transformador de viewport deste objeto. */
    ViewportTransform& viewportTransform() { return transform; }
    const ViewportTransform& viewportTransform() const { return transform; }
};
#endif // SCREEN_RENDERER_H
