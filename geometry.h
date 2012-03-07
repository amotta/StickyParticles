//
//  geometry.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/4/12.
//

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>

#include "vector.h"

typedef struct {
    double r;
    vect_t pos;
} circ_t;

typedef struct {
    double left;
    double right;
    double bottom;
    double top;
} rect_t;

extern bool geoIsCircInCirc(circ_t circInt, circ_t circExt);
extern bool geoIsCircInRect(circ_t circ, rect_t rect);

#endif
