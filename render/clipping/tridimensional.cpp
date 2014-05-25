/* tridimensional.cpp
 * Implementação de tridimensional.h
 */
#include "tridimensional.h"

bool tridimensional( Math::Vector<3>& p, Math::Vector<3>& q ) {
    if( p[2] >= 1 && q[2] >= 1 )
        return true;
    if( p[2] <= 1 && q[2] <= 1 )
        return false;

    Math::Vector<3>& u = p[2] >= 1 ? p : q;
    Math::Vector<3>& v = p[2] >= 1 ? q : p;
    /* Ou p ou q está antes do plano [z == 1]; u aponta para
     * o ponto que está após e v para o que estava antes. */

    // Inclinação em x e em y:
    double cx = (u[0] - v[0])/(u[2] - v[2]);
    double cy = (u[1] - v[1])/(u[2] - v[2]);

    auto px = [&cx, &v]( double z ) -> double {
        return v[0] + cx * (z - v[2]);
    };
    auto py = [&cy, &v]( double z ) -> double {
        return v[1] + cy * (z - v[2]);
    };
    /* px é a função afim que satisfaz
     * px( v[2] ) == v[0]
     * px( u[2] ) == u[0]
     * py é a função afim que satisfaz
     * py( v[2] ) == v[1]
     * py( u[2] ) == v[1]
     * Desta forma, {px(z), py(z), z} sempre estará sobre a reta
     * que passa pelos pontos u e v. Basta então alterar v para
     * {px(1), py(1), 1}. */
    v[0] = px(1);
    v[1] = py(1);
    v[2] = 1;
    return true;
}
