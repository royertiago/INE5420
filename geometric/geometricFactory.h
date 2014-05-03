/* geometricFactory.h
 *
 * Namespace que encapsula uma fábrica de objetos transformáveis.
 */
#ifndef GEOMETRIC_FACTORY_H
#define GEOMETRIC_FACTORY_H

#include <initializer_list>

#include <type_traits>
#include "utility/variadic.h" // para asserts

#include "math/point.h"
#include "polygon.h"

namespace GeometricFactory {

    /* Constrói um polígono com os vetores passados. 
     *
     * Devido ao fato de listas de inicialização delimitadas por chaves
     * (brace-enclose initializer list) não poderem ter seu tipo deduzido
     * (nem para std::initializer_list), para que esta função pudesse
     * aceitar listas de inicialização, ela deveria aceitar apenas
     * listas de inicialização, possivelmente de tipos diferentes. */
    template< typename ... Params >
    Polygon * makePolygon( std::initializer_list<Params> ... );



//Implementações

template< typename ... Ts >
Polygon * makePolygon( std::initializer_list<Ts> ... args ) {
    static_assert( logical_and<
            std::is_convertible< Ts, double >::value ...
        >::value, "Apenas listas de inicialização de tipos"
                  " convertíveis para double!" );
    return new Polygon( new Math::Point<2>[sizeof...(args)]{args...}, 
            sizeof...(args) );
}


} // namespace GeometricFactory


#endif // GEOMETRIC_FACTORY_H
