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

// checks if circle circ is completely in rectangle rect
extern bool isCircInRect(circ_t circ, rect_t rect);

// checks if circ is completely in game rectangle
extern bool isCircInGameRect(circ_t circ);

// checks if particle part is completely in game circle
extern bool isPartInGameCirc(part_t* part);

// checks if particle part is completely in game rectangle
extern bool isPartInGameRect(part_t* part);

// checks if point given by vect is in circle circExt
extern bool isVectInCirc(vect_t vect, circ_t circExt);

// checks if point given by vect is in game circle
extern bool isVectInGameCirc(vect_t vect);

// checks if point given by vect is in rectangle rect
extern bool isVectInRect(vect_t vect, rect_t rect);

// checks if point given by vect is in game rectangle
extern bool isVectInGameRect(vect_t vect);

#endif
