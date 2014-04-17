/* drawablePoint.h
 * Objeto geométrico que representa um ponto.
 * 
 * Embora um ponto deva corresponder a apenas um pixel na tela,
 * este ponto desenha, de fato, uma circunferência pequena ao
 * redor do ponto em questão; isto o torna visível. */
#ifndef DRAWABLE_POINT_H
#define DRAWABLE_POINT_H

#include "transformableObject.h"
#include "linearOperator.h"
#include "point.h"

class Renderer;

class DrawablePoint : public TransformableObject<2> {
    Point<2> p;

public:
    DrawablePoint( Point<2> p ) : p(p) {}

    DrawablePoint() = default;
    DrawablePoint( const DrawablePoint& ) = default;
    DrawablePoint( DrawablePoint&& ) = default;

    virtual ~DrawablePoint() = default;

    //Métodos herdados
    virtual void draw( Renderer* ) override;
    virtual void transform( const LinearOperator<2>& ) override;
    virtual Point<2> center() const;
};



//Definição das funções mais simples

inline void DrawablePoint::transform( const LinearOperator<2>& op ) {
    p = op( p );
}

inline Point<2> DrawablePoint::center() const {
    return p;
}

#endif // DRAWABLE_POINT_H
