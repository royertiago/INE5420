/* matrix.test.cpp
 * Teste de unidade da classe matriz.
 * Algumas funcionalidades desta classe estão disponíveis apenas
 * para matrizes com uma única coluna; estas funcionalidades
 * são testadas em vector.test.cpp */

#include "math/matrix.h"
#include "test/lib/test.h"

DECLARE_TEST( MatrixTest ) {
    Test::TesterMatrix t; //Epsilon de máquina.
    bool b = true;
    using Math::Matrix;
    Matrix<2, 3> m{{0, 1, 2}, 
                   {3, 4, 5}};

    // Teste de acesso
    b &= Test::TEST_EQUALS( m[0][0], 0.0 );
    b &= Test::TEST_EQUALS( m[0][1], 1.0 );
    b &= Test::TEST_EQUALS( m[0][2], 2.0 );
    b &= Test::TEST_EQUALS( m[1][0], 3.0 );
    b &= Test::TEST_EQUALS( m[1][1], 4.0 );
    b &= Test::TEST_EQUALS( m[1][2], 5.0 );

    // Teste de modificação
    m[0][0] = 1.0;
    m[0][1] = 5.0;
    m[0][2] = 3.0;
    m[1][0] = 2.0;
    m[1][1] = 8.0;
    m[1][2] = 7.0;
    b &= t.TEST_EQUALS( m, (Matrix<2, 3>{{1, 5, 3}, 
                                         {2, 8, 7}}) );

    // Operador unário -
    b &= t.TEST_EQUALS( -m, (Matrix<2, 3>{{-1, -5, -3}, {-2, -8, -7}}) );

    // Multiplicação de matrizes
    auto mult = m * Matrix<3, 4>{{ 1,  0,  0,  5},
                                 { 2,  4,  0,  2},
                                 {-1, -1, -1, -1}};
    b &= t.TEST_EQUALS( mult, (Matrix<2, 4>{{ 8, 17, -3, 12},
                                           {11, 25, -7, 19}}) );

    // Atribuição
    m = Matrix<2, 3>{{ 8, 17,  -3},
                     {14, 33, -11}};
    b &= t.TEST_EQUALS( m, (Matrix<2, 3>{{ 8, 17,  -3},
                                         {14, 33, -11}}) );

    // Soma
    Matrix<2, 3> n{{ -7, -16, 4},
                   {-13, -32, 12}};
    b &= t.TEST_EQUALS( m + n, (Matrix<2, 3>{{1, 1, 1},
                                             {1, 1, 1}}) );

    // Subtração
    Matrix<2, 3> o{{1, 1, 0},
                   {2, 1, 0}};
    b &= t.TEST_EQUALS( m + n - o, (Matrix<2, 3>{{ 0, 0, 1},
                                                 {-1, 0, 1}}) );

    // Multiplicação por escalar
    b &= t.TEST_EQUALS( (m + n - o)*3, (Matrix<2, 3>{{ 0, 0, 3},
                                                     {-3, 0, 3}}) );
    return b;                                   
}              
