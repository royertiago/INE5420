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
     * disponível na window; o renderizador cuidará disso. */
    virtual void draw( Renderer * ) = 0;

    virtual ~GeometricObject() = default;
};
#endif // GEOMETRIC_OBJECT_H
