//
//  graphics.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/1/12.
//

#include <math.h>
#include <stdbool.h>
#include <OpenGL/gl.h>

#include "circle.h"
#include "graphics.h"

#define CIRC_SEGMENTS 360

static double color[3];

void gfxCirc(circ_t* circ, bool filled){
    int i = 0;
    double posX, posY;
    double radius;
    double angle;
    
    if(!circ) return;
    
    posX = vectGetX(circGetPos(circ));
    posY = vectGetY(circGetPos(circ));
    radius = circGetRadius(circ);
    angle = 2 * M_PI / CIRC_SEGMENTS;
    
    if(filled){
        glBegin(GL_POLYGON);
    }else{
        glBegin(GL_LINE_LOOP);
    }
    
    for(i = 0; i < CIRC_SEGMENTS; i++){
        glVertex3f(
            posX + cos(angle * i) * radius,
            posY + sin(angle * i) * radius,
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