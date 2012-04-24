//
//  graphics.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/1/12.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>

#include "circle.h"
#include "rectangle.h"

extern void gfxCirc(circ_t circ, bool filled);
extern void gfxClear();
extern void gfxColor(double r, double g, double b);
extern void gfxLine(double x1, double y1, double x2, double y2);
extern void gfxRect(rect_t rect, bool filled);

#endif
