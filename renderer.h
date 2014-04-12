/* renderer.h
 * Classe responsável por transportar objetos do modelo interno
 * do sistema gráfico para o modelo externo.
 *
 * Esta é a classe responsável por fazer a transformada de viewport.
 */

#include "viewportTransform.h"
#include "drawable.h"
#include "pixel.h"

class Renderer {
    ViewportTransform transform; // Transform
    Drawable * screen; // Screen

public:
    /* Constrói um renderizador que utilizará a tela screen para
     * desenhar o que lhe for ordenado, de acordo com o transformador
     * passado.
     *
     * Esta classe não é a "proprietária" do Drawable passado; ela
     * não irá limpar o ponteiro na deleção. */
    Renderer( ViewportTransform transform, Drawable * screen );

    /* Desenha na tela a reta que passa pelos referidos pontos,
     * de acordo com a posição decidida pela transformada de viewport
     * escolhida no construtor. */
    template< int N >
    void drawLine( const Point<N>& origin, const Point<N>& destiny );

    /* Retorna o transformador de viewport deste objeto. */
    ViewportTransform& viewportTransform() { return transform; }
    const ViewportTransform& viewportTransform() const { return transform; }
};

template< int N >
void Renderer::drawLine( const Point<N>& origin, const Point<N>& destiny ) {
    Pixel a = transform.transform( origin );
    Pixel b = transform.transform( destiny );
    screen->paint( a, b );
}
