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

// draws circ as filled or empty circle
extern void gfxCirc(circ_t circ, bool filled);

// clear the current buffer
extern void gfxClear();

// change current color to rgb
extern void gfxColor(double r, double g, double b);

// draw line from point x1, y1 to x2, y2
extern void gfxLine(double x1, double y1, double x2, double y2);

// draw rect as filled of empty rectangle
extern void gfxRect(rect_t rect, bool filled);

#endif
