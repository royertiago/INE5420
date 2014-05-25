/* displayFile.h
 * Esta classe contém a lista de todos os objetos que devem ser desenhados
 *  - apareçam eles na tela ou não. */

#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <map>
#include <string>
#include <utility>
#include "geometric/transformableObject.h"
#include "math/affineOperator.h"
#include "math/vector.h"
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
    void draw( Renderer<N> * );

    /* Deleta todos os objetos contidos no DisplayFile. */
    void clear();

    /* Transforma o objeto especificado pela string. */
    void transform( std::string name, const Math::AffineOperator<N>& op );

    /* Informa o centro do objeto. */
    Math::Vector<N> center( std::string name );

    /* Remove e deleta o objeto especificado do DisplayFile. */
    void remove( std::string name );

    ~DisplayFile();
};

// Implementação

template< int N >
DisplayFile<N>::~DisplayFile() {
    for( auto& pair : objects )
        delete pair.second;
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
void DisplayFile<N>::draw( Renderer<N> * renderer ) {
    for( auto& pair : objects )
        pair.second->draw( renderer );
}

template< int N >
void DisplayFile<N>::clear() {
    for( auto& pair : objects )
        delete pair.second;
    objects.clear();
}

template< int N >
void DisplayFile<N>::transform( std::string n, 
        const Math::AffineOperator<N>& op )
{
    auto iterator = objects.find( n );
    if( iterator == objects.end() )
        return;

    iterator->second->transform( op );
}

template< int N >
Math::Vector<N> DisplayFile<N>::center( std::string name ) {
    return objects[name]->center();
}

template< int N >
void DisplayFile<N>::remove( std::string name ) {
    delete objects[name];
    objects.erase( name );
}
#endif // DISPLAY_FILE_H
