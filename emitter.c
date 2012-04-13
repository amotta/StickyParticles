//
//  emitter.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "emitter.h"
#include "vector.h"

struct EMITTER {
    vect_t* pos;
    double alpha;
    double flow;
    double speed;
};

emitter_t* emitterNew(){
    emitter_t* emitter = NULL;
    
    if((emitter = malloc(sizeof(emitter_t)))){
        emitterInit(emitter);
    }else{
        printf("Could not allocate memory for new emitter\n");
        exit(EXIT_FAILURE);
    }
    
    return emitter;
}

void emitterInit(emitter_t* emitter){
    if(!emitter) return;
    
    vectFree(emitter->pos);
    emitter->pos = NULL;
    
    emitter->alpha = 0;
    emitter->flow = 0;
    emitter->speed = 0;
}

void emitterSetPos(emitter_t* emitter, vect_t* pos){
    if(!emitter || !pos) return;
    
    emitter->pos = pos;
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
    
    emitterInit(emitter);
    free(emitter);
}