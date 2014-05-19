/* linearOperator.cpp
 * Contém as implementações das funções não templatizadas.
 */

#include <cstdio>
#include <cmath>
using std::sqrt;
using std::fabs;
using std::printf;

#include "math/linearOperator.h"
#include "math/constant.h"
using namespace Math;

LinearOperator<2> LinearFactory::Rotation2D( double d, Point<2> c ) {
    LinearOperator<2> o = Translation<2>( c );
    o.frontComposeWith( Rotation<2>( d, 0, 1 ) );
    o.frontComposeWith( Translation<2>( -c ) );
    return o;
}

static double epsilon = 1e-10;

LinearOperator<3> LinearFactory::AxisAlignment( Vector<3> front, Vector<3> up )
{
    Vector<3> xyFproj = front; // [xz]-plane [f]ront vector [proj]ection
    xyFproj[2] = 0.0; // O importante é o ângulo.
    LinearOperator<3> r;
    if( fabs(xyFproj[1]) > epsilon ) 
        if( xyFproj[1] > 0 )
            r = Rotation<3>( vectorAngle(xyFproj, {1,0,0}), 1, 0 );
        else
            r = Rotation<3>( vectorAngle(xyFproj, {1,0,0}), 0, 1 );
    else
        r = Scale<3>(1);

    /* O objetivo é formar, inicialmente, um operador linear que rotacione
     * o vetor front para o plano xz, sobre o eixo z.
     *
     * Considere, então, o vetor xyFproj: o que queremos fazer é rodar 
     * o plano determinado por front e xyFproj para o plano xz.
     * Note que os vetores front, xyFproj e {0, 0, 1} são coplanares.
     * O ângulo entre o plano em que eles estão contidos e o plano xz
     * é o mesmo que o ângulo entre xyFproj e o vetor unitário
     * {1, 0, 0} (que está alinhado com o eixo x), pois eles estão no mesmo
     * plano sobre o qual ocorrerá a rotação.
     *
     * Mas é importante notar a orientação: se xzFproj estiver do lado
     * "positivo" do plano (isto é, sua coordenada y for positiva), 
     * a rotação deve ser do eixo y para o eixo x,
     * e na direção contrária no outro caso.
     *
     * Há um caso especial (que é tratado pelo if externo): caso o valor
     * da componente y seja nula, o vetor já está no plano xz, e nada
     * precisa ser feito. */

    front = Vector<3>( r(Point<3>(front)) );
    if( front[0] >= 0 )
        r.backComposeWith( Rotation<3>(vectorAngle(front, {0,0,1}), 0, 2) );
    else
        r.backComposeWith( Rotation<3>(vectorAngle(front, {0,0,1}), 2, 0) );
    /* Mesma ideia, mas agora rotacionando para coincidir com o eixo z.
     * Não precisamos mais fazer projeções pois o vetor front já está
     * no plano correto, basta rotacionar para o eixo correto.
     *
     * Para o próximo passo (fazer up coincidir com {0, 1, 0}, precisamos
     * saber como up se comporta sob a transformação até aqui: */
    Vector<3> upR = Vector<3>( r( Point<3>(up) ) ); // up [r]otated
    if( upR[0] >= 0 )
        r.backComposeWith( Rotation<3>(vectorAngle(upR, {0,1,0}), 0, 1) );
    else
        r.backComposeWith( Rotation<3>(vectorAngle(upR, {0,1,0}), 1, 0) );
    
    return r;
}

LinearOperator<3> LinearFactory::InverseAxisAlignment( 
        Vector<3> front, Vector<3> up )
{
    Vector<3> xyFproj = front;
    xyFproj[2] = 0.0;
    LinearOperator<3> t; // [t]emporary transform
    LinearOperator<3> r; // [r]eturn transform
    if( fabs(xyFproj[1]) > epsilon ) 
        if( xyFproj[1] > 0 ) {
            t = Rotation<3>( vectorAngle(xyFproj, {1,0,0}), 1, 0 );
            r = Rotation<3>( -vectorAngle(xyFproj, {1,0,0}), 1, 0 );
        }
        else {
            t = Rotation<3>( vectorAngle(xyFproj, {1,0,0}), 0, 1 );
            r = Rotation<3>( -vectorAngle(xyFproj, {1,0,0}), 0, 1 );
        }
    else {
        t = Scale<3>(1);
        r = Scale<3>(1);
    }
    /* A ideia é a mesma. Faremos em t a mesma transformação feita
     * em AxisAlignment e em r a transformação inversa. */

    front = Vector<3>( t(Point<3>(front)) );
    if( front[0] >= 0 ) {
        t.backComposeWith( Rotation<3>(vectorAngle(front, {0,0,1}), 0, 2) );
        r.frontComposeWith( Rotation<3>(-vectorAngle(front, {0,0,1}), 0, 2) );
    }
    else {
        t.backComposeWith( Rotation<3>(vectorAngle(front, {0,0,1}), 2, 0) );
        r.frontComposeWith( Rotation<3>(-vectorAngle(front, {0,0,1}), 2, 0) );
    }
    /* Note que temos que compor no sentido contrário: a última transformação
     * feita é a primeira a ser desfeita. */

    Vector<3> upR = Vector<3>( t( Point<3>(up) ) ); // up [r]otated
    if( upR[0] >= 0 )
        r.frontComposeWith( Rotation<3>(-vectorAngle(upR, {0,1,0}), 0, 1) );
    else
        r.frontComposeWith( Rotation<3>(-vectorAngle(upR, {0,1,0}), 1, 0) );
    /* Não precisamos fazer o último cálculo com a transformação
     * não-invertida, pois não a usaremos mais. */

    return r; 
    // Isto é mais custoso do que inverter no braço...
}
