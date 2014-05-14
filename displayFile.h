/* displayFile.h
 * Esta classe contém a lista de todos os objetos que devem ser desenhados
 *  - apareçam eles na tela ou não. */

#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <map>
#include <string>
#include <utility>

#include "geometric/transformableObject.h"
#include "math/linearOperator.h"
#include "render/renderer.h"

template< int N >
class DisplayFile {
    std::map< std::string, TransformableObject<N>* > objects;
    
public:
    DisplayFile() = default;
    DisplayFile( const DisplayFile& ) = default;
    DisplayFile( DisplayFile&& ) = default;

    /* Adiciona o objeto geométrico à lista de objetos a serem
     * desenhados.
     *
     * O displayFile assume responsabilidade sobre o ponteiro,
     * deletando-o quando o construtor é chamado.
     *
     * Caso já haja um objeto com o mesmo nome na lista, este
     * objeto será deletado antes da inserção deste. */
    void addObject( std::string name, TransformableObject<N> * object );

    /* Desenha todos os objetos geométricos armazenados neste
     * DisplayFile no renderizador passado. */
    void draw( Renderer * );

    /* Transforma o objeto especificado pela string. */
    void transform( std::string name, Math::LinearOperator<N>& op );

    ~DisplayFile();
};

// Implementação

template< int N >
void DisplayFile<N>::draw( Renderer * renderer ) {
    for( auto& pair : objects )
        pair.second->draw( renderer );
}

template< int N >
void DisplayFile<N>::addObject( std::string n, TransformableObject<N>* obj ) {
    auto iterator = objects.insert( std::make_pair( n, obj ) );

    if( iterator.second )
        return;

    delete iterator.first->second;
    iterator.first->second = obj;
}

template< int N >
DisplayFile<N>::~DisplayFile() {
    for( auto& pair : objects )
        delete pair.second;
}

template< int N >
void DisplayFile<N>::transform( std::string n, Math::LinearOperator<N>& op ) {
    auto iterator = objects.find( n );
    if( iterator == objects.end() )
        return;

    iterator.second->transform( op );
}

#endif // DISPLAY_FILE_H
