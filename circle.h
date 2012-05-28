//
//  circle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdbool.h>

#include "vector.h"

typedef struct {
    vect_t pos;
    double r;
} circ_t;

// Checks if circInt is completely in circExt
extern bool isCircInCirc(circ_t circInt, circ_t circExt);

// Checks if circ is completely in the game circle
extern bool isCircInGameCirc(circ_t circ);

// Checks if circOne and circTwo intersect
extern bool circCheckCirc(circ_t circOne, circ_t circTwo);

// Checks if circ touches the borders.
// circCheckBorder DIR_LEFT, DIR_RIGHT, DIR_TOP, DIR_BOTTOM or DIR_NONE
extern int circCheckBorder(circ_t circ);

// Returns the projection of from on to
extern circ_t circProjectOnCirc(circ_t from, circ_t to);

// Returns the null circle
extern circ_t circGetNull();

// Returns the game circle
extern circ_t getGameCirc();

#endif
