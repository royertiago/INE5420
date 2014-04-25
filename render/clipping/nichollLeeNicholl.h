/* nichollLeeNicholl.h
 */
#ifndef NICHOLL_LEE_NICHOLL_H
#define NICHOLL_LEE_NICHOLL_H

#include "lineClipper.h"

#include "clippingArea.h"
#include "math/point.h"

class NichollLeeNicholl : public LineClipper<2> {
private:
    ClippingArea clippingArea;

public:
    /* Construtores */
    /* Cria e vincula à área de clipping 'a' */
    NichollLeeNicholl( ClippingArea a );

    virtual void setArea( ClippingArea ) override;
    virtual bool clip( Math::Point<2>&, Math::Point<2>& ) override;

    virtual ~NichollLeeNicholl() = default;
    
private:
    /* Funções privadas que auxiliam o clipping */
    bool isInsideMyClippingArea( Math::Point<2>& );
};

#endif // NICHOLL_LEE_NICHOLL_H
