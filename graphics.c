//
//  graphics.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/1/12.
//

#include <math.h>
#include <stdbool.h>

#ifDEF __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include "circle.h"
#include "graphics.h"
#include "rectangle.h"

#define CIRC_SEGMENTS 120

static double color[3];

void gfxCirc(circ_t circ, bool filled){
    int i;
    double angle;
    
    // calculate angle
    angle = 2 * M_PI / CIRC_SEGMENTS;
    
    if(filled){
        glBegin(GL_POLYGON);
    }else{
        glBegin(GL_LINE_LOOP);
    }
    
    for(i = 0; i < CIRC_SEGMENTS; i++){
        glVertex3f(
            circ.pos.x + cos(angle * i) * circ.r,
            circ.pos.y + sin(angle * i) * circ.r,
            0
        );
    }
    
    glEnd();
}

void gfxClear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void gfxColor(double r, double g, double b){
    glColor3d(r, g, b);
    glClearColor(r, g, b, 1);
}

void gfxLine(double x1, double y1, double x2, double y2){
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glEnd();
}

void gfxRect(rect_t rect, bool filled){
    if(filled){
        glBegin(GL_POLYGON);
    }else{
        glBegin(GL_LINE_LOOP);
    }
    
    glVertex3f(rect.left, rect.top, 0);
    glVertex3f(rect.right, rect.top, 0);
    glVertex3f(rect.right, rect.bottom, 0);
    glVertex3f(rect.left, rect.bottom, 0);
    
    glEnd();
}