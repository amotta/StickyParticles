//
//  circle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdbool.h>

#include "rectangle.h"
#include "vector.h"

typedef struct {
    double r;
    vect_t pos;
} circ_t;

extern bool isCircInCirc(circ_t circInt, circ_t circExt);
extern bool isCircInRect(circ_t circ, rect_t rect);

#endif
