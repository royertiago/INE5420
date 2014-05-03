/* weilerAtherton.h
 * 
 * Algoritmo de clipping de polígonos; implementa polygonClipper.
 */
 
#ifndef WEILER_ATHERTON_H
#define WEILER_ATHERTON_H

#include "render/clipping/polygonClipper.h"

#include "render/clipping/clippingArea.h"

#include <vector>  // std::vector

#include "geometric/polygon.h"
#include "geometric/geometricFactory.h"
#include "utility/circularLinkedList.h"
#include "math/point.h"

class WeilerAtherton : public PolygonClipper<2> {
private:
    ClippingArea ca;
    
public:
    /* Cria e vincula à área de clipping 'a' */
    WeilerAtherton( ClippingArea a);
    
    virtual void setArea( ClippingArea ) override;
    virtual std::vector<Polygon> clip( Polygon& ) override;
    
    
    
    // Funções que auxiliam o algoritmo:
    
    // "Math::Point<2> pontoDeInterceccao" é um parâmetro que será
    // modificado a fim de informar, caso o retorno seja "true", em
    // qual ponto os dois segmentos de reta se cruzam.
    bool pontoDeInterceccao(Math::Point<2>& inicioReta1,
                            Math::Point<2>& fimReta1,
                            Math::Point<2>& inicioReta2,
                            Math::Point<2>& fimReta2,
                            Math::Point<2>& pontoDeInterceccao);
};

#endif // WEILER_ATHERTON_H
