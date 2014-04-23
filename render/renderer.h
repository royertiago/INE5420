/* renderer.h
 * Classe abstrata que representa qualquer objeto capaz de fazer
 * renderização.
 *
 * O renderer se baseia nas coordenadas do mundo e as transforma para
 * coordenadas da viewport. O passo intermediário (transformação
 * para coordenadas da window) é feito implicitamente pelo renderizador,
 * que também é responsável pelo clipping das retas e polígonos.
 *
 * Um exemplo de implementação concreta é ScreenRenderer, que é 
 * capaz de renderizar para um drawable.h
 */
#ifndef RENDERER_H
#define RENDERER_H

#include "math/point.h"
#include "render/window.h"

class Renderer {
public:
    /* Desenha na tela o segmento de reta que passa pelos 
     * referidos pontos. */
    virtual void drawLine( Math::Point<2> origin, Math::Point<2> destiny ) = 0;

    /* Desenha na tela o polígono representado pelos pontos
     * passados.
     * Interpretaremos este polígono como sendo um polígono preenchido. */
    virtual void drawPolygon( Math::Point<2> * points, int numPoints ) = 0;

    /* Obtém a densidade da tela.
     *
     * A densidade é a quantidade de pixels que são utilizados,
     * em média, para representar um quadrado de lado 1.
     *
     * Esta informação pode ser utilizada pelos objetos que usam
     * este renderizador para calibrar o detalhamento do desenho. */
    virtual double density() = 0;
    
    virtual ~Renderer() = default;
};
#endif // RENDERER_H
