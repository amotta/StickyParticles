//
//  circle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdbool.h>

typedef struct {
    vect_t pos;
    double r;
} circ_t;

extern circ_t getGameCirc();
extern bool isCircInCirc(circ_t circInt, circ_t circExt);
extern bool isCircInGameCirc(circ_t circ);

#endif
