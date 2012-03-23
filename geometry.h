//
//  geometry.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/23/12.
//

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>

#include "circle.h"
#include "rectangle.h"

extern bool isCircInRect(circ_t circ, rect_t rect);
extern bool isCircInGameRect(circ_t circ);

#endif
