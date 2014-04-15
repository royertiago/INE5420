/* drawable.h
 * Interface que representa alguma tela na qual podem ser desenhados
 * pixels.
 *
 * Objetos desta interface se comunicam com alguma tela de desenho real;
 * por exemplo, Qt ou SDL.
 *
 * Uma tela desenhável é necessariamente um "pedaço" retangular do plano
 * cartesiano, com a origem no canto superior esquerdo. Aumentar o eixo x
 * significa deslocar-se à direita, enquanto aumentar o y significa deslocar-
 * -se para baixo.
 *
 * Simplesmente executar o método Drawable::paint pode não ser 
 * suficiente para forçar a interface a desenhar alguma coisa.
 * A tela pode esperar que o método Drawable::update seja invocado.
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "pixel.h"

class Drawable {
public:
    /* Altera a cor do pixel a ser desenhado.
     *
     * A cor está em formato RGBA. Os três primeiros parâmetros
     * deverão estar entre 0 e 255 e representam a intensidade
     * de vermelho, verde e azul, respectivamente.
     * O quarto parâmetro também deve estar entre 0 e 255 e representa
     * a transparência do pixel. Uma transparência de 255 significa
     * um pixel "opaco", e uma transparência 0 significa um pixel
     * "invisível".
     */
    virtual void setColor( int r, int g, int b, int a ) = 0;

    /* Pinta o pixel na tela, com a cor (e transparência)
     * definidos anteriormente por Drawable::setColor.
     *
     * p.x deve estar entre 0 (inclusive) e Drawable::width() (exclusive); e
     * p.y deve estar entre 0 (inclusive) e Drawable::height() (exclusive);
     * isto é, o ponto deve estar dentro da tela de desenho.
     */
    virtual void paint( Pixel p ) = 0;

    /* Pinta na tela o segmento de reta que une os pontos a e b,
     * na cor (e transparência) definidos anteriormente por
     * Drawable::setColor.
     *
     * a e b devem se submeter às mesmas exigências do parâmetro
     * do método Drawable::paint( Pixel ); isto é, a reta já deve ter
     * sofrido todos os procedimentos de clipping necessários. */
    virtual void paint( Pixel a, Pixel b ) = 0;

    /* Retorna a altura da tela.
     *
     * Como a origem é o ponto (0, 0), o ponto (0, height()) está fora
     * da área de desenho da tela.
     */
    virtual int height() const = 0;

    /* Retorna a largura da tela.
     *
     * Como a origem é o ponto (0, 0), o ponto (width(), 0) está fora
     * da área de desenho da tela.
     */
    virtual int width() const = 0;

    /* Atualiza a tela de desenho.
     * 
     * Caso a tela seja atualizada automaticamente ao executar o método
     * Desenhavel::pixel, este método pode ser vazio.
     */
    virtual void update() = 0;

    virtual ~Drawable() = default;
};

#endif // DRAWABLE_H
