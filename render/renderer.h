/* renderer.h
 * Classe abstrata que representa qualquer objeto capaz de fazer
 * renderização.
 *
 * São utilizados quatro sistemas de coordenadas: mundo, window, window
 * projetada e viewport.
 *
 * As coordenadas de mundo são as coordenadas "reais" do sistema; estas
 * coordenadas são mapeadas para coordenadas de window baseado na posição
 * da window (que é um objeto do mundo). 
 *
 * Em coordenadas da window, o centro do mundo é o centro da window,
 * o view-up vector aponta para "cima" (no eixo y), a direção de visão
 * está alinhada com o eixo z, dentre outras características que facilitam
 * a projeção e clipping; ver window.h.
 *
 * Por exemplo: num mundo em três dimensões, tanto as coordenadas do mundo 
 * quanto as coordenadas da window estão em três dimensões. Já os sistemas de
 * coordenadas de window projetada e viewport estão em  duas dimensões.
 * Qualquer informação sobre posição espacial, reflexão de luz etc.
 * é perdido ao mapear window para window projetada. 
 *
 * Retas e polígonos já em coordenadas da window são projetadas e aparadas.
 * Estes objetos são projetados no quadrado [-1, 1] x [-1, 1] (em coordenadas
 * de window projetadas), que, mais tarde, serão mapeados para coordenadas de 
 * viewport (em píxels), já prontos para ser desenhados na tela.
 *
 * Para mundos em duas dimensões, as coordenadas de window e coordenadas
 * de window projetada são o mesmo sistema de coordenadas, já que não há
 * projeção. Para mundos tridimensionais, existe a necessidade de haver
 * projeção (pois a tela do computador é bidimensional), então estes sistemas
 * de coordenadas são diferentes; de fato, eles possuem um número diferentes
 * de dimensões.
 *
 * Existem duas principais formas de projetar objetos tridimensionais
 * num espaço bidimensional: projeção paralela e projeção em perspectiva.
 * É decisão do Renderer qual a forma de projeção utilizada.
 *
 * Objetos que implementam esta interface são responsáveis por tomar retas
 * e polígonos em coordenadas de mundo, realizar todas as transformações
 * necessárias para traduzir estas coordenadas para coordenadas de viewport
 * (incluindo projeções e aparos), e desenhar os objetos em alguma tela.
 */
#ifndef RENDERER_H
#define RENDERER_H

#include "math/point.h"

template< int N > // Dimensão dos objetos renderizados
class Renderer {
public:
    /* Desenha na tela o segmento de reta que passa pelos 
     * referidos pontos. */
    virtual void drawLine( Math::Point<N> origin, Math::Point<N> destiny ) = 0;

    /* Desenha o triângulo cujas extremidades são os três
     * pontos passados. 
     * Para desenhar polígonos complexos, ver utility/triangulation.h */
    virtual void drawTriangle( Math::Point<N> p1, Math::Point<N> p2, 
            Math::Point<N> p3 ) = 0;

    /* Obtém a densidade da tela.
     *
     * A densidade é a quantidade de pixels que são utilizados
     * para representar um cubo de dimensão N de lado 1.
     *
     * Esta informação pode ser utilizada pelos objetos que usam
     * este renderizador para calibrar o detalhamento do desenho. */
    virtual double density() const = 0;
    
    virtual ~Renderer() = default;
};
#endif // RENDERER_H
