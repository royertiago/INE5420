/* viewportTransform.h
 * Classe capaz de mapear coordenadas de window para coordenadas
 * de viewport.
 *
 * Objetos deste tipo são normalmente usados após o clipping
 * já ter sido feito.
 */
#ifndef VIEWPORT_TRANSFORM_H
#define VIEWPORT_TRANSFORM_H

#include "view/pixel.h"
#include "render/viewport.h"
#include "render/clipping/clippingArea.h"
#include "math/point.h"

class ViewportTransform {
    Viewport vp;
    const ClippingArea& ca;

public:
    /* Cria um transformador de viewport com a viewport
     * e área de clipping especificadas. */
    ViewportTransform( Viewport viewport, const ClippingArea& clippingArea );

    /* Computa a transformada de viewport para o dado ponto. */
    Pixel transform( Math::Point<2> ) const;
    Pixel operator()( Math::Point<2> ) const;

    /* Computa as coordenadas de window para o dado pixel. */
    Math::Point<2> reverseTransform( Pixel ) const;

    /* Retorna a Viewport deste objeto. */
    const Viewport& viewport() const;
};

//Implementação das funções mais simples

inline ViewportTransform::ViewportTransform( Viewport vp,
        const ClippingArea& ca ) :
    vp( vp ),
    ca( ca )
{}

inline Pixel ViewportTransform::operator()( Math::Point<2> p ) const {
    return transform( p );
}

inline const Viewport& ViewportTransform::viewport() const {
    return vp;
}

#endif // VIEWPORT_TRANSFORM_H
