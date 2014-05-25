/* affineFactory.h
 * Conjunto de funções que auxiliam a criação de operadores afins.
 */
#ifndef AFFINE_FACTORY_H
#define AFFINE_FACTORY_H

#include "math/affineOperator.h"
#include "math/matrix.h"
#include "math/vector.h"

namespace AffineFactory {
    using namespace Math;

    /* Retorna o operador identidade. */
    template< int N >
    AffineOperator<N> identity();

    /* Constrói um operador linear que desloca os pontos
     * na direção especificada. */
    template< int N >
    AffineOperator<N> Translation( Vector<N> direction );

    /* Constrói um operador linear que amplia os pontos
     * pelo fator especificado. Note que esta transformação de escala
     * ocorre em relação à origem do mundo. */
    template< int N >
    AffineOperator<N> Scale( double factor );

    /* Constrói um operador linear que amplia os pontos pelo
     * fator especificado, em relação ao centro especificado. */
    template< int N >
    AffineOperator<N> Scale( double factor, Vector<N> center );

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
    AffineOperator<N> Rotation( double angle, int i, int j );

    /* Constrói um operador linear que rotaciona os pontos
     * com relação ao centro especificado, em sentido anti-horário,
     * pelo ângulo especificado.
     * O ângulo será tratado em radianos. */
    AffineOperator<2> Rotation2D( double angle, Vector<2> center );

    /* Constrói um operador linear que rotaciona os pontos em torno
     * da origem do mundo, sobre o eixo de rotação especificado.
     * O ângulo será tratado em radianos. */
    AffineOperator<3> Rotation3D( double, Vector<3> axis );

    /* Constrói um operador linear que rotaciona os pontos em torno
     * do centro especificado, sobre o eixo de rotação especificado. */
    AffineOperator<3> Rotation3D( double, Vector<3> axis, Vector<3> center );

    /* Constrói um operador linear que transforma os pontos de
     * forma que axis esteja alinhado com o vetor unitário z.
     *
     * Note que tal operador não é único. */
    AffineOperator<3> AxisAlignment( Vector<3> axis );

    /* Constrói um operador linear que transforma os pontos de 
     * forma que front esteja alinhado com o vetor unitário z
     * {0, 0, 1} e up alinhado com o vetor unitário y {0, 1, 0}.
     * 
     * Assumiremos que front e up formam uma base ortogonal para
     * o plano que será mapeado para o plano yz. */
    AffineOperator<3> AxisAlignment( Vector<3> front, Vector<3> up );

    /* Constrói o operador linear inverso de AxisAlignment( axis ). */
    AffineOperator<3> InverseAxisAlignment( Vector<3> axis );

// Implementação

template< int N >
AffineOperator<N> Identity() {
    return AffineOperator<N>( Matrix<N, N>::identity() );
}

template< int N >
AffineOperator<N> Translation( Vector<N> direction ) {
    return AffineOperator<N>( Matrix<N, N>::identity(), direction );
}

template< int N >
AffineOperator<N> Scale( double factor ) {
    return AffineOperator<N>( factor * Matrix<N, N>::identity() );
}

template< int N >
AffineOperator<N> Scale( double factor, Vector<N> center ) {
    return Translation<N>( -center ).
        backComposeWith( Scale<N>( factor ) ).
        backComposeWith( Translation<N>( center ) );
}

template< int N >
AffineOperator<N> Rotation( double angle, int m, int j ) {
    Matrix<N, N> r = Matrix<N, N>::identity();
    r[m][m] =  std::cos( angle );
    r[j][j] =  std::cos( angle );
    r[m][j] = -std::sin( angle );
    r[j][m] =  std::sin( angle );
    return AffineOperator<N>( r );
}

} // namespace AffineFactory

#endif // AFFINE_FACTORY_H
