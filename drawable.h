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
 * Simplesmente executar o método Desenhavel::pixel pode não ser suficiente
 * para forçar a interface a desenhar alguma coisa. A tela pode esperar
 * que o método Desenhavel::atualizar seja invocado.
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

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

    /* Pinta o pixel (x, y) na tela, com a cor (e transparência)
     * definidos anteriormente por Desenhavel::alterarCor.
     *
     * x deve estar entre 0 (inclusive) e Drawable::width() (exclusive); e
     * y deve estar entre 0 (inclusive) e Drawable::height() (exclusive).
     */
    virtual void pixel( int x, int y ) = 0;

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
