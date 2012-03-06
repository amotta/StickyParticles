//
//  circle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/4/12.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdbool.h>

#include "vector.h"

typedef struct {
    double r;
    vect_t pos;
} circ_t;

extern bool isCircleInCircle(circ_t circInt, circ_t circExt);

#endif
