//
//  graphics.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/1/12.
//

#include <math.h>
#include <OpenGL/gl.h>

#include "circle.h"

#define CIRC_SEGMENTS 360

static void gfxColor(int color);
static void gfxCircle(circ_t* circ);

enum GFX_COLOR_CODES {
    GFX_CLEAR_COLOR,
    GFX_GAMECIRC_COLOR
};

static double GFX_COLOR_RGBS[][3] = {
    {1.00, 1.00, 1.00},
    {0.75, 0.00, 0.00}
};

void gfxCircle(circ_t* circ){
    int i = 0;
    
    glBegin(GL_LINE_LOOP);
    for(i = 0; i < CIRC_SEGMENTS; i++){
        glVertex3f(
            vectGetX(circGetPos(circ))
            + cos(2 * M_PI / CIRC_SEGMENTS * i) * circGetRadius(circ),
            vectGetY(circGetPos(circ))
            + sin(2 * M_PI / CIRC_SEGMENTS * i) * circGetRadius(circ),
            0
        );
    }
    
    glEnd();
}

void gfxClear(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void gfxColor(int color){
    glColor3d(
        GFX_COLOR_RGBS[color][0],
        GFX_COLOR_RGBS[color][1],
        GFX_COLOR_RGBS[color][2]
    );
}

void gfxGameCirc(){
    gfxColor(GFX_GAMECIRC_COLOR);
    // TODO
    // gfxCircle(gameCirc);
}

