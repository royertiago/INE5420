/* point.test.cpp
 * Teste de unidade para Math::Point.
 * Um ponto n-dimensional funciona de forma idêntica a um vetor
 * (n+1)-dimensional, e testes para estes comportamentos estão
 * acessíveis em test/vector.test.cpp; aqui, testaremos a conversão
 * implícita entre estes dois "tipos".
 */

#include "math/point.h"
#include "math/vector.h"
#include "test/lib/testEquals.h"
#include "test/lib/testMacro.h"
#include "test/lib/declarationMacros.h"

#include <cstdio>
using namespace std;

DECLARE_TEST( PointTest ) {
    bool b = true;
    using namespace Math;

    // Testar se a última posição é preenchida corretamente com 1
    Vector<2> v = {1.0, 2.0};
    Point<2> p( v );
    Test::TEST_EQUALS( p[2], 1.0 );

    // Mesmo teste, com listas de inicialização
    p = Point<2>{1.0, 2.0};
    Test::TEST_EQUALS( p[2], 1.0 );

    return b;
}
