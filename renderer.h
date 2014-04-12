/* renderer.h
 * Classe responsável por transportar objetos do modelo interno
 * do sistema gráfico para o modelo externo.
 *
 * Esta é a classe responsável por fazer a transformada de viewport.
 */

#include "window.h"
#include "viewport.h"
#include "drawable.h"

class Renderer {
    Renderer( Window window, Viewport viewport, Drawable* screen );

    drawLine( Vector<2> origin, Vector<2> destiny );
    //TODO: terminar
};
