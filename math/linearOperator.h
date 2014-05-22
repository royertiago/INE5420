/* linearOperator.h
 * Contém a definição de um operador linear: uma transformação linear
 * que mapeia um espaço vetorial para si mesmo.
 *
 * Neste caso, o operador linear transforma pontos.
 */
#ifndef LINEAR_OPERATOR_H
#define LINEAR_OPERATOR_H

#include <cmath>
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
    using namespace Math;

    /* Constrói um operador linear que desloca os pontos
     * na direção especificada. */
    template< int N >
    LinearOperator<N> Translation( Math::Vector<N> direction );

    /* Constrói um operador linear que amplia os pontos
     * pelo fator especificado. Note que esta transformação de escala
     * ocorre em relação à origem do mundo.
     * Note que Scale(1) é a matriz identidade. */
    template< int N >
    LinearOperator<N> Scale( double factor );

    /* Constrói um operador linear que amplia os pontos pelo
     * fator especificado, em relação ao centro especificado. */
    template< int N >
    LinearOperator<N> Scale( double factor, Point<N> center );

    /* Constrói um operador linear que rotaciona os pontos
     * no plano ij, no sentido i->j.
     *
     * O ângulo será tratado em radianos.
     * i e j começam do zero.
     *
     * Por exemplo, para fazer uma rotação no plano xz no sentido
     * x -> z num espaço tridimensional, chame
     *  auto op = Rotation<3>( angle, 0, 2 );
     * op({0, 0, 1}) deve ser igual a {1, 0, 0} para angle = Pi/2.
     * A transformação de rotação padrão em duas dimensões é obtida via
     *  Rotation<2>( angle, 0, 1 ); */
    template< int N >
    LinearOperator<N> Rotation( double angle, int i, int j );

    /* Constrói um operador linear que rotaciona os pontos
     * com relação ao centro especificado, em sentido anti-horário,
     * pelo ângulo especificado.
     * O ângulo será tratado em radianos. */
    LinearOperator<2> Rotation2D( double angle, Point<2> center );

    /* Constrói um operador linear que rotaciona os pontos em torno
     * da origem do mundo, sobre o eixo de rotação especificado.
     * O ângulo será tratado em radianos. */
    LinearOperator<3> Rotation3D( double, Vector<3> axis );

    /* Constrói um operador linear que rotaciona os pontos em torno
     * do centro especificado, sobre o eixo de rotação especificado. */
    LinearOperator<3> Rotation3D( double, Vector<3> axis, Point<3> center );

    /* Constrói um operador linear que transforma os pontos de
     * forma que axis esteja alinhado com o vetor unitário z.
     *
     * Note que tal operador não é único. */
    LinearOperator<3> AxisAlignment( Vector<3> axis );

    /* Constrói um operador linear que transforma os pontos de 
     * forma que front esteja alinhado com o vetor unitário z
     * {0, 0, 1} e up alinhado com o vetor unitário y {0, 1, 0}.
     * 
     * Assumiremos que front e up formam uma base ortogonal para
     * o plano que será mapeado para o plano yz. */
    LinearOperator<3> AxisAlignment( Vector<3> front, Vector<3> up );

    /* Constrói o operador linear inverso de AxisAlignment( axis ). */
    LinearOperator<3> InverseAxisAlignment( Vector<3> axis );

// Implementação
template< int N >
LinearOperator<N> Translation( Vector<N> direction ) {
    LinearOperator<N> r; //retorno
    for( int i = 0; i <= N; ++i )
        r[i][i] = 1.0;
    for( int i = 0; i < N; ++i )
        r[i][N] = direction[i];
    return r;
}

template< int N >
LinearOperator<N> Scale( double factor ) {
    LinearOperator<N> r;
    int i = 0;
    for( ; i < N; ++i )
        r[i][i] = factor;
    r[i][i] = 1.0;
    return r;
}

template< int N >
LinearOperator<N> Scale( double factor, Point<N> center ) {
    LinearOperator<N> r = Translation<N>( -center );
    r.backComposeWith( Scale<N>( factor ) );
    r.backComposeWith( Translation<N>( center ) );
    return r;
}

template< int N >
LinearOperator<N> Rotation( double angle, int m, int j ) {
    LinearOperator<N> r = Scale<N>( 1 );
    r[m][m] =  std::cos( angle );
    r[j][j] =  std::cos( angle );
    r[m][j] = -std::sin( angle );
    r[j][m] =  std::sin( angle );
    return r;
}

} // namespace LinearFactory

#endif // LINEAR_OPERATOR_H
