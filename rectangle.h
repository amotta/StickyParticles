//
//  rectangle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>

#include "constants.h"
#include "vector.h"

typedef struct {
    double left;
    double right;
    double bottom;
    double top;
} rect_t;

extern rect_t gameRect;

extern bool isVectInRect(vect_t vect, rect_t rect);
extern bool isVectInGameRect(vect_t vect);

#endif
