/* transformableObject.h
 * Objeto geométrico que pode sofrer transformações lineares.
 */
#ifndef TRANSFORMABLE_OBJECT_H
#define TRANSFORMABLE_OBJECT_H

#include "geometric/geometricObject.h"
#include "math/point.h"
#include "math/linearOperator.h"

template< int N >
class TransformableObject : public GeometricObject {
public:
    /* Aplica a transformação linear passada no objeto.
     * O objeto é livre para determinar o melhor momento
     * de propagar a transformação; isto é, ele pode armazenar
     * a lista de todas as transformações que devem ser
     * aplicadas a ele e só as aplicar logo antes de desenhar;
     * entretanto, assumiremos que o que quer que o objeto
     * desenhe no renderizador, seja já com as devidas
     * transformações. */
    virtual void transform( const Math::LinearOperator< N >& ) = 0;

    /* Informa o centro do objeto em questão.
     * Esta informação pode ser usada para criar transformações
     * de escala e de rotação centradas no objeto. */
    virtual Math::Point<N> center() const = 0;

    virtual ~TransformableObject() = default;
};

#endif // TRANSFORMABLE_OBJECT_H
