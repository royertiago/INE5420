/* transformableObject.h
 * Objeto geométrico que pode sofrer transformações lineares.
 */
#ifndef TRANSFORMABLE_OBJECT_H
#define TRANSFORMABLE_OBJECT_H

#include "geometric/geometricObject.h"
#include "math/vector.h"
#include "math/affineOperator.h"

template< int N >
class TransformableObject : public GeometricObject<N> {
public:
    /* Aplica a transformação afim passada no objeto. */
    virtual void transform( const Math::AffineOperator< N >& ) = 0;

    /* Informa o centro do objeto em questão.
     * Esta informação pode ser usada para criar transformações
     * de escala e de rotação centradas no objeto. */
    virtual Math::Vector<N> center() const = 0;

    virtual ~TransformableObject() = default;
};

#endif // TRANSFORMABLE_OBJECT_H
