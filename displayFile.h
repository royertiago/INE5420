/* displayFile.h
 * Esta classe contém a lista de todos os objetos que devem ser desenhados
 *  - apareçam eles na tela ou não. */

#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <vector>

class GeometricObject;
class Renderer;

class DisplayFile {
    std::vector< GeometricObject* > objects;
public:
    DisplayFile() = default;
    DisplayFile( const DisplayFile& ) = default;
    DisplayFile( DisplayFile&& ) = default;

    /* Adiciona o objeto geométrico à lista de objetos a serem
     * desenhados.
     *
     * O displayFile assume responsabilidade sobre o ponteiro,
     * deletando-o quando o construtor é chamado. */
    void addObject( GeometricObject * object ) {
        objects.push_back( object );
    }

    /* Desenha todos os objetos geométricos armazenados neste
     * DisplayFile no renderizador passado. */
    void draw( Renderer * );

    ~DisplayFile();
};

#endif // DISPLAY_FILE_H
