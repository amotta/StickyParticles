//
//  emitter.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "emitter.h"
#include "graphics.h"
#include "rectangle.h"
#include "vector.h"

#define EMITTER_SIZE 0.1
#define MAX_EMITTER_LEN 1.0

struct EMITTER {
    vect_t* pos;
    double angle;
    double alpha;
    double flow;
    double speed;
};

emitter_t* emitterNew(){
    emitter_t* emitter = NULL;
    
    if((emitter = malloc(sizeof(emitter_t)))){
        emitter->pos = NULL;
        emitter->angle = 0;
        emitter->alpha = 0;
        emitter->flow = 0;
        emitter->speed = 0;
    }else{
        printf("Could not allocate memory for new emitter\n");
        exit(EXIT_FAILURE);
    }
    
    return emitter;
}

vect_t* emitterGetPos(emitter_t* emitter){
    if(!emitter) return NULL;
    
    return emitter->pos;
}

void emitterSetPos(emitter_t* emitter, vect_t* pos){
    double diffX, diffY;
    
    if(!emitter || !pos) return;
    
    // set pos
    emitter->pos = pos;
    
    // update angle
    diffX = vectGetX(emitter->pos) - vectGetX(getGameCenter());
    diffY = vectGetY(emitter->pos) - vectGetY(getGameCenter());
    
    emitter->angle = atan2(diffY, diffX) + M_PI;
}

double emitterGetAngle(emitter_t* emitter){
    if(!emitter) return 0;
    
    return emitter->angle;
}

double emitterGetAlpha(emitter_t* emitter){
    if(!emitter) return 0;
    
    return emitter->alpha;
}

void emitterSetAlpha(emitter_t* emitter, double alpha){
    if(!emitter) return;
    
    emitter->alpha = alpha;
}

void emitterSetFlow(emitter_t* emitter, double flow){
    if(!emitter) return;
    
    emitter->flow = flow;
}

double emitterGetSpeed(emitter_t* emitter){
    if(!emitter) return 0;
    
    return emitter->speed;
}

void emitterSetSpeed(emitter_t* emitter, double speed){
    if(!emitter) return;
    
    emitter->speed = speed;
}

bool emitterDraw(emitter_t* emitter){
    static rect_t* rect = NULL;
    
    double lineLen;
    double posX, posY;
    double alphaOne, alphaTwo;
    
    if(!rect){
        rect = rectNew();
    }
    
    if(!emitter) return false;
    
    posX = vectGetX(emitterGetPos(emitter));
    posY = vectGetY(emitterGetPos(emitter));
    
    // alphas
    alphaOne = emitterGetAngle(emitter) - emitterGetAlpha(emitter);
    alphaTwo = emitterGetAngle(emitter) + emitterGetAlpha(emitter);
    
    // line length
    lineLen = MAX_EMITTER_LEN / MAX_VG * emitterGetSpeed(emitter);
    
    gfxColor(0, 0, 0);
    gfxLine(
        posX, posY,
        posX + lineLen * cos(alphaOne), posY + lineLen * sin(alphaOne)
    );
    gfxLine(
        posX, posY,
        posX + lineLen * cos(alphaTwo), posY + lineLen * sin(alphaTwo)
    );
    
    // draw rect
    rectSetLeft(rect, posX - EMITTER_SIZE / 2);
    rectSetRight(rect, posX + EMITTER_SIZE / 2);
    rectSetBottom(rect, posY - EMITTER_SIZE / 2);
    rectSetTop(rect, posY + EMITTER_SIZE / 2);
    
    gfxRect(rect, true);
}

void emitterFree(emitter_t* emitter){
    if(!emitter) return;
    
    vectFree(emitter->pos);
    free(emitter);
}