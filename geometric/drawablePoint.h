/* drawablePoint.h
 * Objeto geométrico que representa um ponto.
 * 
 * Embora um ponto deva corresponder a apenas um pixel na tela,
 * este ponto desenha, de fato, uma circunferência pequena ao
 * redor do ponto em questão; isto o torna visível. */
#ifndef DRAWABLE_POINT_H
#define DRAWABLE_POINT_H

#include <cmath>
using std::sqrt;
using std::sin;
using std::cos;

#include "geometric/transformableObject.h"
#include "math/constant.h"
#include "math/linearOperator.h"
#include "math/point.h"
#include "render/renderer.h"

template< int N >
class DrawablePoint : public TransformableObject<N> {
    Math::Point<N> p;

public:
    /* Cria um DrawablePoint em p. */
    DrawablePoint( Math::Point<N> p ) : p(p) {}

    DrawablePoint() = default;
    DrawablePoint( const DrawablePoint& ) = default;
    DrawablePoint( DrawablePoint&& ) = default;
    virtual ~DrawablePoint() = default;

    //Métodos herdados
    virtual void draw( Renderer<N>* ) override;
    virtual void transform( const Math::LinearOperator<N>& ) override;
    virtual Math::Point<N> center() const;
};

//Implementação

template< int N >
void DrawablePoint<N>::transform( const Math::LinearOperator<N>& op ) {
    p = op( p );
}

template< int N >
Math::Point<N> DrawablePoint<N>::center() const {
    return p;
}

template< int N >
void DrawablePoint<N>::draw( Renderer<N> * renderer ) {
    using Math::PI;
    double density = renderer->density();
    static const double radius = 2 / sqrt(density);
    
    Math::Point<N> alce = p;
    alce[0] = alce[1] = alce[N] = 0.0;
    // Usaremos 12 retas para desenhar o círculo:
    double theta = 2* PI / 12;
    for( int i = 0; i < 12; i++ ) {
        renderer->drawLine(
            Math::Point<N>({ p[0] + radius * cos(i*theta),
                             p[1] + radius * sin(i*theta)}) + alce,
            Math::Point<N>({ p[0] + radius * cos((i+1)*theta), 
                             p[1] + radius * sin((i+1)*theta)}) + alce
       );
    }
    /* Desta forma, variamos as duas primeiras coordenadas do ponto
     * e as últimas ficam iguais às de p. */
}

#endif // DRAWABLE_POINT_H
