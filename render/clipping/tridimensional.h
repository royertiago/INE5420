/* tridimensional.h
 * Clipping de retas simples em três dimensões, baseado em CohenSutherland.
 *
 * Possui assinatura compatível com a de lineClipper.h.
 */
#ifndef TRIDIMENSIONAL_H
#define TRIDIMENSIONAL_H

#include "math/point.h"

bool tridimensional( Math::Point<3>&, Math::Point<3>& );

#endif // TRIDIMENSIONAL_H
