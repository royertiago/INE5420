/* weilerAtherton.cpp
 * Implementação de weilerAtherton.h
 */
 
#include "weilerAtherton.h"

#include "render/clipping/clippingArea.h"

#include <vector>  // std::vector

#include "geometric/polygon.h"
#include "geometric/geometricFactory.h"
#include "utility/circularLinkedList.h"
#include "math/point.h"

WeilerAtherton::WeilerAtherton( ClippingArea a ):
    ca(a)
{}

void WeilerAtherton::setArea( ClippingArea a) {
    ca = a;
}

std::vector<Polygon> WeilerAtherton::clip( Polygon& subjectPolygon ) {    
    // Lista circular que conterá os pontos que definem a área de clipping
    CircularLinkedList<Math::Point<2>> *clipList = new CircularLinkedList<Math::Point<2>>;
    // Inserir pontos que definem a área de clipping em sentido horário
    clipList->add({ca.xmin, ca.ymin});
    clipList->add({ca.xmin, ca.ymax});
    clipList->add({ca.xmax, ca.ymax});
    clipList->add({ca.xmax, ca.ymin});
    
    // Lista circular que conterá os vértices do polígono que receberá o clipping
    CircularLinkedList<Math::Point<2>> *subjectList = new CircularLinkedList<Math::Point<2>>;
    // Inserir os vértices do polígono que receberá o clipping em sentido horário
    // TODO: Invocar função que ordena pontos do polígono em sentido horário, por
    // enquanto assumir que o polígono foi criado passando-lhe pontos em sentido horário
    int numberOfSubjectVertices = subjectPolygon.getVertexCount();
    const Math::Point<2> *subjectVertices = subjectPolygon.getVertices();
    for(int i = 0; i < numberOfSubjectVertices; i++)
        subjectList->add(subjectVertices[i]);
    
    // TODO: Adicionar intersecções entre o polígono objeto e a área de clipping às listas
    
    
    std::vector<Polygon> afterClippingPolygons;
    
    afterClippingPolygons.push_back(subjectPolygon);
       
    delete clipList; delete subjectList;
    return afterClippingPolygons;
}

bool WeilerAtherton::pontoDeInterceccao(Math::Point<2>& inicioReta1,
                                        Math::Point<2>& fimReta1,
                                        Math::Point<2>& inicioReta2,
                                        Math::Point<2>& fimReta2,
                                        Math::Point<2>& pontoDeInterceccao)
{
    return false;
}
