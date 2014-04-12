/* drawablePoint.h
 * Objeto geométrico que representa um ponto.
 * 
 * Embora um ponto deva corresponder a apenas um pixel na tela,
 * este ponto desenha, de fato, uma circunferência pequena ao
 * redor do ponto em questão; isto o torna visível. */
#ifndef DRAWABLE_POINT_H
#define DRAWABLE_POINT_H

#include "geometricObject.h"
#include "point.h"

class Renderer;

class DrawablePoint : public GeometricObject {
    Point<2> p;

public:
    DrawablePoint( Point<2> p ) : p(p) {}

    DrawablePoint() = default;
    DrawablePoint( const DrawablePoint& ) = default;
    DrawablePoint( DrawablePoint&& ) = default;

    virtual ~DrawablePoint() = default;

    virtual void draw( Renderer* ) override;
};

#endif // DRAWABLE_POINT_H
