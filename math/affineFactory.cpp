/* affineFactory.cpp
 * Contém as implementações das funções não templatizadas de affineFactory.h.
 */

#include "math/affineFactory.h"
#include "math/constant.h"
using namespace Math;

AffineOperator<2> AffineFactory::Rotation2D( double d, Vector<2> c ) {
    return Translation<2>( c ).
        frontComposeWith( Rotation<2>( d, 0, 1 ) ).
        frontComposeWith( Translation<2>( -c ) );
}

AffineOperator<3> AffineFactory::Rotation3D( double d, Vector<3> v ) {
    return AxisAlignment( v ).
        backComposeWith( Rotation<3>( d, 0, 1 ) ).
        backComposeWith( InverseAxisAlignment( v ) );
}

AffineOperator<3> AffineFactory::Rotation3D( double d, Vector<3> v, 
        Vector<3> c )
{
    return Translation<3>( -c ).
        backComposeWith( Rotation3D( d, v ) ).
        backComposeWith( Translation<3>( c ) );
}

static double epsilon = 1e-10;

AffineOperator<3> AffineFactory::AxisAlignment( Vector<3> axis ) {
    Vector<3> xyproj = axis; // [xy]-plane vector [proj]ection
    xyproj[2] = 0.0; // O importante é o ângulo.
    AffineOperator<3> r;
    if( fabs(xyproj[1]) > epsilon ) 
        if( xyproj[1] > 0 )
            r = Rotation<3>( vectorAngle(xyproj, {1,0,0}), 1, 0 );
        else
            r = Rotation<3>( vectorAngle(xyproj, {1,0,0}), 0, 1 );
    else
        r = Identity<3>();

    /* O objetivo é formar, inicialmente, um operador linear que rotacione
     * o vetor para o plano xz, sobre o eixo z.
     *
     * Considere, então, o vetor xyproj: o que queremos fazer é rodar 
     * o plano determinado por front e xyproj para o plano xz.
     * Note que os vetores axis, xyproj e {0, 0, 1} são coplanares.
     * O ângulo entre o plano em que eles estão contidos e o plano xz
     * é o mesmo que o ângulo entre xyproj e o vetor unitário
     * {1, 0, 0} (o eixo x), pois eles estão no mesmo plano sobre o qual
     * ocorrerá a rotação.
     *
     * Mas é importante notar a orientação: se xzproj estiver do lado
     * "positivo" do plano (isto é, sua coordenada y for positiva), 
     * a rotação deve ser do eixo y para o eixo x, e na direção contrária 
     * no outro caso.
     *
     * Há um caso especial (que é tratado pelo if externo): caso o valor
     * da componente y seja nula, o vetor já está no plano xz, e nada
     * precisa ser feito. De fato, existe a possibilidade de axis
     * já estar alinhada com o eixo z; xyproj seria, portanto, o vetor
     * nulo, e teríamos uma divisão por zero. */

    axis = r( axis );
    if( axis[0] >= 0 )
        r.backComposeWith( Rotation<3>(vectorAngle(axis, {0,0,1}), 0, 2) );
    else
        r.backComposeWith( Rotation<3>(vectorAngle(axis, {0,0,1}), 2, 0) );
    /* Mesma ideia, mas agora rotacionando para coincidir com o eixo z.
     * Não precisamos mais fazer projeções pois o vetor front já está
     * no plano correto, basta rotacionar para o eixo desejado. */
    return r;
}

AffineOperator<3> AffineFactory::AxisAlignment( Vector<3> front, Vector<3> up )
{
    AffineOperator<3> r = AxisAlignment( front );
    /* A primeira parte (alinhar front com o eixo z) já é tratada pela
     * função AxisAlignment( Vector<3> ).
     *
     * O próximo passo é fazer up coincidir com {0, 1, 0}. Precisamos
     * saber como up se comporta sob a transformação até aqui, e
     * aplicar a mesma lógica da função AxisAlignment( Vector<3> ). */
    Vector<3> upR = r( up ); // up [r]otated
    if( upR[0] >= 0 )
        r.backComposeWith( Rotation<3>(vectorAngle(upR, {0,1,0}), 0, 1) );
    else
        r.backComposeWith( Rotation<3>(vectorAngle(upR, {0,1,0}), 1, 0) );
    
    return r;
}

AffineOperator<3> AffineFactory::InverseAxisAlignment( Vector<3> axis ) {
    Vector<3> xyproj = axis;
    xyproj[2] = 0.0;
    AffineOperator<3> t; // [t]emporary transform
    AffineOperator<3> r; // [r]eturn transform
    if( fabs(xyproj[1]) > epsilon ) 
        if( xyproj[1] > 0 ) {
            t = Rotation<3>( vectorAngle(xyproj, {1,0,0}), 1, 0 );
            r = Rotation<3>( -vectorAngle(xyproj, {1,0,0}), 1, 0 );
        }
        else {
            t = Rotation<3>( vectorAngle(xyproj, {1,0,0}), 0, 1 );
            r = Rotation<3>( -vectorAngle(xyproj, {1,0,0}), 0, 1 );
        }
    else {
        t = Identity<3>();
        r = Identity<3>();
    }
    /* Faremos em t a mesma transformação feita em AxisAlignment 
     * e em r a transformação inversa. */

    axis = t( axis );
    if( axis[0] >= 0 )
        r.frontComposeWith( Rotation<3>(-vectorAngle(axis, {0,0,1}), 0, 2) );
    else
        r.frontComposeWith( Rotation<3>(-vectorAngle(axis, {0,0,1}), 2, 0) );
    /* Note que temos que compor no sentido contrário: a última transformação
     * feita é a primeira a ser desfeita. */

    return r; 
}
