/* linearOperator.h
 * Classe que representa um operador linear: uma transformação linear
 * que mapeia um espaço vetorial para si mesmo.
 *
 * Neste caso, o operador linear transforma pontos.
 */

#include <initializer_list>

#include "point.h"
#include "math/matrix.h"
#include "math/vector.h"

template <int N>
class LinearOperator {
    /* Matematicamente, operadores lineares entre espaços n-dimensionais
     * são representados por matrizes NxN. Como um Point n-dimensional
     * encapsula um vetor n+1-dimensional (para que translação seja uma
     * transformação linear), precisamos, internamente, realizar 
     * transformações num espaço n+1-dimensional. */
    Math::Matrix<N+1, N+1> matrix;

public:
    LinearOperator( const Math::Matrix<N+1, N+1>& );

    /* Listas de inicialização.
     * Inicializa todas as posições possíveis para os valores correspondentes
     * e os demais para zero.
     * Valores adicionais são ignorados. */
    LinearOperator( std::initializer_list<std::initializer_list<double>> );
    
    LinearOperator() = default;
    LinearOperator( const LinearOperator<N>& ) = default;
    LinearOperator( LinearOperator<N>&& ) = default;

    /* Aplica a transformação linear no ponto passado. */
    Point<N> transform( const Point<N>& p ) const {
        return matrix * (p.vector);
    }
    Point<N> transform( Point<N>&& p ) const {
        return matrix * (p.vector);
    }

    /* Aplica a transformação linear no ponto passado. */
    Point<N> operator()( const Point<N>& p ) const {
        return transform( p );
    }
    Point<N> operator()( Point<N>&& p ) const {
        return transform( std::forward(p) );
    }

    /* Compõe este operador linear com o passado, e retorna
     * o resultado. As operações comportar-se-ão como se o vetor
     * escolhido for dado ao operador op e o resultado disso dado
     * a este operador. */
    LinearOperator<N> compose( const LinearOperator<N>& op ) const {
        return LinearOperator<N>( matrix * op.matrix );
    }
    /* Compõe este operador linear com o passado. As operações comportar-
     * -se-ão como se os vetores passados sejam dados antes ao operador op
     *  e o resultado alimentado este operador. */
    void frontComposeWith( const LinearOperator<N>& op ) {
        matrix = matrix * op.matrix;
    }
    /* Compõe o operador linear passado com este. As operações comportar-
     * -se-ão como se os vetores passados sejam dados a este operador
     *  e o resultado entregue ao operador op. */
    void backComposeWith( const LinearOperator<N>& op ) {
        matrix = op.matrix * matrix;
    }
};

/* Constrói um operador linear que desloca os pontos
 * na direção especificada. */
LinearOperator<2> make2DTranslation( Math::Vector<2> direction );

/* Constrói um operador linear que amplia os pontos
 * pelo fator especificado. Note que esta transformação de escala
 * ocorre em relação à origem do mundo. */
LinearOperator<2> make2DScale( double factor );

/* Constrói um operador linear que amplia os pontos pelo
 * fator especificado, em relação ao centro especificado. */
LinearOperator<2> make2DScale( double factor, Point<2> center );

/* Constrói um operador linear que rotaciona os pontos
 * em sentido anti-horário, em relação ao mundo.
 * O ângulo será tratado em radianos. */
LinearOperator<2> make2DRotation( double angle );

/* Constrói um operador linear que rotaciona os pontos
 * com relação ao centro especificado, em sentido anti-horário,
 * pelo ângulo especificado.
 * O ângulo será tratado em radianos. */
LinearOperator<2> make2DRotation( double angle, Point<2> center );

template <int N>
LinearOperator<N>::LinearOperator( const Math::Matrix<N+1, N+1>& m ) :
    matrix(m)
{}

template <int N>
LinearOperator<N>::LinearOperator( 
        std::initializer_list<std::initializer_list<double>> list )
{
    auto it = list.begin();
    int i = 0;
    for( ; it != list.end() && i <= N; ++i, ++it ) {
        auto jt = it->begin();
        int j = 0;
        for( ; jt != it->end() && j <= N; ++j, ++jt )
            matrix[i][j] = *jt;
        for( ; j <= N; ++j )
            matrix[i][j] = 0.0;
    }
    for( ; i <= N; ++i )
        for( int j = 0; j <= N; ++j )
            matrix[i][j] = 0.0;
}
