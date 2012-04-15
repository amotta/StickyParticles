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

typedef struct CIRC circ_t;

extern circ_t* circNew();
extern vect_t* circGetPos(circ_t* circ);
extern void circSetPos(circ_t* circ, vect_t* vect);
extern double circGetRadius(circ_t* circ);
extern void circSetRadius(circ_t* circ, double radius);
extern void circFree(circ_t* circ);

extern circ_t* getGameCirc();
extern bool isCircInCirc(circ_t* circInt, circ_t* circExt);
extern bool isCircInGameCirc(circ_t* circ);
extern bool isVectInCirc(vect_t* vect, circ_t* circExt);
extern bool isVectInGameCirc(vect_t* vect);

#endif
