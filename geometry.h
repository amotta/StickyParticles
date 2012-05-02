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
#include "particle.h"
#include "rectangle.h"
#include "vector.h"

#define DIR_NONE (0)
#define DIR_LEFT (1 << 1)
#define DIR_RIGHT (1 << 2)
#define DIR_BOTTOM (1 << 3)
#define DIR_TOP (1 << 4)

extern bool isCircInRect(circ_t circ, rect_t rect);
extern bool isCircInGameRect(circ_t circ);
extern bool isPartInGameCirc(part_t* part);
extern bool isPartInGameRect(part_t* part);
extern bool isVectInCirc(vect_t vect, circ_t circExt);
extern bool isVectInGameCirc(vect_t vect);
extern bool isVectInRect(vect_t vect, rect_t rect);
extern bool isVectInGameRect(vect_t vect);

#endif
