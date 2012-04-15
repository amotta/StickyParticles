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
#include "vector.h"

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

void emitterSetSpeed(emitter_t* emitter, double speed){
    if(!emitter) return;
    
    emitter->speed = speed;
}

void emitterFree(emitter_t* emitter){
    if(!emitter) return;
    
    vectFree(emitter->pos);
    free(emitter);
}