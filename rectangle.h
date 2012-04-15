//
//  rectangle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>

typedef struct RECT rect_t;

extern rect_t* rectNew();
extern double rectGetLeft(rect_t* rect);
extern void rectSetLeft(rect_t* rect, double left);
extern double rectGetRight(rect_t* rect);
extern void rectSetRight(rect_t* rect, double right);
extern double rectGetBottom(rect_t* rect);
extern void rectSetBottom(rect_t* rect, double bottom);
extern double rectGetTop(rect_t* rect);
extern void rectSetTop(rect_t* rect, double top);
extern void rectFree(rect_t* rect);

extern rect_t* getGameRect();

#endif
