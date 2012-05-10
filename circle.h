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

extern bool isCircInCirc(circ_t circInt, circ_t circExt);
extern bool isCircInGameCirc(circ_t circ);
extern bool circCheckCirc(circ_t circOne, circ_t circTwo);
extern int circCheckBorder(circ_t circ);
extern circ_t circProjectOnCirc(circ_t from, circ_t to);
extern circ_t circGetNull();
extern circ_t getGameCirc();

#endif
