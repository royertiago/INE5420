/* renderer.h
 * Classe abstrata que representa qualquer objeto capaz de fazer
 * renderização.
 *
 * Um exemplo de implementação concreta é ScreenRenderer, que é 
 * capaz de renderizar para um drawable.h
 */
#ifndef RENDERER_H
#define RENDERER_H

#include "point.h"
#include "window.h"

class Renderer {
public:
    /* Desenha na tela o segmento de reta que passa pelos 
     * referidos pontos. */
    virtual void drawLine( Point<2> origin, Point<2> destiny ) = 0;

    /* Obtém a densidade da tela.
     *
     * A densidade é a quantidade de pixels que são utilizados
     * para representar um quadrado de lado 1 alinhado aos eixos.
     *
     * Esta informação pode ser utilizada pelos objetos que usam
     * este renderizador para calibrar o detalhamento do desenho. */
    virtual double density() = 0;
    
    /* Retorna a window que está sendo desenhada por este renderizador.
     *
     * Esta informação pode ser utilizada por objetos mais complexos
     * para determinar se ele será desenhado, para evitar desperdiçar
     * ciclos de processamento com objetos que não serão mostrados. */
    virtual Window window() = 0;

    virtual ~Renderer() = default;
};
#endif // RENDERER_H
