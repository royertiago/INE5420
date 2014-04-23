/* windowTransform.cpp
 * Implementação do único método complexo de windowTransform.h:
 * computeTransform()
 */

#include "render/windowTransform.h"
#include "render/clipping/clippingArea.h"
#include "math/linearOperator.h"
#include "math/vector.h"
#include "window.h"

using LinearFactory::make2DTranslation;
using LinearFactory::make2DRotation;

void WindowTransform::computeTransform() const {
    ClippingArea ca = this->clippingArea();
    Math::Vector<2> CAcenter = {(ca.xmax - ca.xmin) / 2,
                                (ca.ymax - ca.ymin) / 2};
    lo = make2DTranslation( {-w.x, -w.y} );
    /* Acabo de deslocar o centro da window para o centro do mundo.
     * Agora, usaremos as transformações com base na origem do mundo
     * para deixar a transformação alinhada com a área de clipping,
     * e depois é só deslocar tudo para o centro CAcenter. */
    
    lo.backComposeWith( make2DRotation( -w.t ) );
    //Agora, os eixos de ambos estão na orientação correta.

    Math::LinearOperator<2> scale = { { (ca.xmax - ca.xmin)/w.w, 0, 0 },
                                { 0, (ca.ymax - ca.ymin)/w.h, 0 },
                                { 0, 0, 1 }
                              };

    lo.backComposeWith( scale );

    lo.backComposeWith( make2DTranslation( CAcenter ) );
}
