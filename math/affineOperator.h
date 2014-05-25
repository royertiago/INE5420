/* affineOperator.h
 * Classe que transforma vetores de forma (quase) linear.
 *
 * Um operador afim f satisfaz: se g(x) = f(x) - f(0), então
 * g é um operador linear. Quer dizer, um operador afim é a soma
 * de um operador linear com um vetor de deslocamento.
 *
 * Operadores afins estão definidos apenas para double.
 */
#ifndef AFFINE_OPERATOR_H
#define AFFINE_OPERATOR_H

#include "math/matrix.h"
#include "math/vector.h"

namespace Test {
    class AffineTester;
}

namespace Math {

template< int N >
class AffineOperator {
    Matrix<N, N> m; // [m]atriz-base
    Vector<N> v; // [v]etor de deslocamento

    friend class Test::AffineTester;
public:
    
    /* Constrói o operador nulo. */
    AffineOperator() = default;

    /* Constrói um operador afim a partir da matriz e do vetor
     * especificados. 
     *
     * Como o vetor de deslocamento especificado é, por padrão,
     * o vetor nulo, este construtor pode ser usado para converter,
     * implicitamente, uma matriz NxN para um operador afim. */
    AffineOperator( Matrix<N, N>, Vector<N> = Vector<N>() );

    /* Aplica esta transformação afim no vetor passado. */
    Vector<N> transform( const Vector<N>& ) const;
    Vector<N> operator()( const Vector<N>& ) const;

    /* Compõe este operador com o operador passado. As operações comportar-
     * -se-ão como se os objetos passados sejam dados antes à transformação
     * afim op e o resultado alimentado esta transformação; isto é,
     * a transformação passada vai ficar "na frente" desta.
     *
     * Retorna este objeto. */
    AffineOperator<N>& frontComposeWith( const AffineOperator<N>& op );

    /* Compõe o operador passado com este operador. As operações comportar-
     * -se-ão como se os vetores passados sejam dados a esta transformação
     * afim e o resultado entregue à transformação op; isto é,
     * a transformação passada vai ficar "atrás" desta. 
     *
     * Retorna este objeto. */
    AffineOperator<N>& backComposeWith( const AffineOperator<N>& op );
};

// Implementação
template< int N >
AffineOperator<N>::AffineOperator( Matrix<N, N> m, Vector<N> v ) :
    m( m ),
    v( v )
{}

template< int N >
Vector<N> AffineOperator<N>::transform( const Vector<N>& x ) const {
    return m * x + v;
}

template< int N >
Vector<N> AffineOperator<N>::operator()( const Vector<N>& x ) const {
    return transform( x );
}

template< int N >
AffineOperator<N>& AffineOperator<N>::frontComposeWith( 
        const AffineOperator<N>& op )
{
    /* Temos (se T = *this)
     * T( x ) = m * x + v
     * OP( x ) = op.m * x + op.v
     * Queremos
     * S( x ) = T(OP( x ))
     *        = T(op.m * x + op.v)
     *        = m * (op.m * x + op.v) + v
     *        = m*op.m * x + m*op.v + v */
    v = m * op.v + v;
    m = m * op.m;
    return *this;
}

template< int N >
AffineOperator<N>& AffineOperator<N>::backComposeWith( 
        const AffineOperator<N>& op )
{
    /* Temos (se T = *this)
     * T( x ) = m * x + v
     * OP( x ) = op.m * x + op.v
     * Queremos
     * S( x ) = OP(T( x ))
     *        = OP(m * x + v)
     *        = op.m * (m * x + v) + op.v
     *        = op.m*m * x + op.m*v + op.v */
    v = op.m * v + op.v;
    m = op.m * m;
    return *this;
}

} // namespace Math


#endif // AFFINE_OPERATOR_H
