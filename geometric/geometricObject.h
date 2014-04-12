/* geometricObject.h
 * Representa um objeto geométrico.
 *
 * Objetos geométricos sabem como desenhar-se através de um
 * renderizador. */

#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

class Renderer;

class GeometricObject {
public:
    /* Desenha este objeto geométrico no renderizador passado.
     *
     * O objeto não precisa cuidar de desenhar apenas na área
     * disponível na window; o renderizador cuidará disso.
     *
     * Note que, se o objeto estiver fora da window, pode ser
     * que o renderizador não se altere em virtude do desenho. */
    virtual void draw( Renderer* ) = 0;

    virtual ~GeometricObject() = default;
};
#endif // GEOMETRIC_OBJECT_H
