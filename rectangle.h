//
//  rectangle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>

#include "vector.h"

typedef struct RECT rect_t;

extern rect_t* rectNew();
extern void rectFree(rect_t* rect);

extern rect_t* getGameRect();
extern bool isVectInRect(vect_t* vect, rect_t* rect);
extern bool isVectInGameRect(vect_t* vect);

#endif
