/* linearOperator.h
 * Contém a definição de um operador linear: uma transformação linear
 * que mapeia um espaço vetorial para si mesmo.
 *
 * Neste caso, o operador linear transforma pontos.
 */
#ifndef LINEAR_OPERATOR_H
#define LINEAR_OPERATOR_H

#include "math/matrix.h"
#include "math/vector.h"
#include "math/point.h"

namespace Math {

    /* Mais uma vez abusamos do fato de o typedef ser não-estrito. */
    template <int N>
    using LinearOperator = Matrix<N+1, N+1>;

} // namespace Math

/* Namespace que contém funções para construir operadores lineares
 * capazes de efetuar operações específicas. */
namespace LinearFactory {
    using Math::LinearOperator;

    /* Constrói um operador linear que desloca os pontos
     * na direção especificada. */
    LinearOperator<2> make2DTranslation( Math::Vector<2> direction );

    /* Constrói um operador linear que amplia os pontos
     * pelo fator especificado. Note que esta transformação de escala
     * ocorre em relação à origem do mundo. */
    LinearOperator<2> make2DScale( double factor );

    /* Constrói um operador linear que amplia os pontos pelo
     * fator especificado, em relação ao centro especificado. */
    LinearOperator<2> make2DScale( double factor, Math::Point<2> center );

    /* Constrói um operador linear que rotaciona os pontos
     * em sentido anti-horário, em relação ao mundo.
     * O ângulo será tratado em radianos. */
    LinearOperator<2> make2DRotation( double angle );

    /* Constrói um operador linear que rotaciona os pontos
     * com relação ao centro especificado, em sentido anti-horário,
     * pelo ângulo especificado.
     * O ângulo será tratado em radianos. */
    LinearOperator<2> make2DRotation( double angle, Math::Point<2> center );

} // namespace LinearFactory

#endif // LINEAR_OPERATOR_H
