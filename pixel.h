/* pixel.h
 * Tipo POD que representa um pixel.
 *
 * Este tipo é usado para passar dados entre as classes que estão
 * em contato direto com a interface gráfica (da viewport para
 * frente).
 */

#ifndef PIXEL_H
#define PIXEL_H

struct Pixel {
    int x;
    int y;
};

#endif // PIXEL_H
