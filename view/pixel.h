/* pixel.h
 * Tipo POD que representa um pixel, em coordenadas de viewport.
 *
 * Este tipo é usado para passar dados entre as classes que estão
 * em contato direto com a interface gráfica (da viewport para
 * frente).
 *
 * As coordenadas deste objeto são compatíveis com a representação
 * utilizada pela maioria das interfaces gráficas: o canto superior
 * esquerdo é a origem, e, ao descer o ponto, o valor de y aumenta
 * ao invés de diminuir.
 */

#ifndef PIXEL_H
#define PIXEL_H

struct Pixel {
    int x;
    int y;
};

#endif // PIXEL_H
