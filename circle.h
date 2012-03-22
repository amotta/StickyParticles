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

extern const circ_t gameCirc;

extern bool isCircInCirc(circ_t circInt, circ_t circExt);
extern bool isCircInGameCirc(circ_t circ);
extern bool isCircInRect(circ_t circ, rect_t rect);
extern bool isCircInGameRect(circ_t circ);
extern bool isVectInCirc(vect_t vect, circ_t circExt);
extern bool isVectInGameCirc(vect_t vect);

#endif
