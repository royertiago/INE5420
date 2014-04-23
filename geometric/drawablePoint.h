/* drawablePoint.h
 * Objeto geométrico que representa um ponto.
 * 
 * Embora um ponto deva corresponder a apenas um pixel na tela,
 * este ponto desenha, de fato, uma circunferência pequena ao
 * redor do ponto em questão; isto o torna visível. */
#ifndef DRAWABLE_POINT_H
#define DRAWABLE_POINT_H

#include "geometric/transformableObject.h"
#include "math/linearOperator.h"
#include "math/point.h"

class Renderer;

class DrawablePoint : public TransformableObject<2> {
    Math::Point<2> p;

public:
    DrawablePoint( Math::Point<2> p ) : p(p) {}

    DrawablePoint() = default;
    DrawablePoint( const DrawablePoint& ) = default;
    DrawablePoint( DrawablePoint&& ) = default;

    virtual ~DrawablePoint() = default;

    //Métodos herdados
    virtual void draw( Renderer* ) override;
    virtual void transform( const Math::LinearOperator<2>& ) override;
    virtual Math::Point<2> center() const;
};



//Definição das funções mais simples

inline void DrawablePoint::transform( const Math::LinearOperator<2>& op ) {
    p = op( p );
}

inline Math::Point<2> DrawablePoint::center() const {
    return p;
}

#endif // DRAWABLE_POINT_H
