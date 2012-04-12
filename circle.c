//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#include <stdbool.h>

#include "circle.h"
#include "constants.h"
#include "vector.h"

struct CIRC {
    vect_t* pos;
    double r;
};

circ_t* circNew(){
    circ_t* circ = NULL;
    
    if(circ = malloc(sizeof(circ_t))){
        circInit(circ);
    }else{
        printf("Could not allocate memory for new circle\n");
        exit(EXIT_FAILURE);
    }
    
    return circ;
}

void circInit(circ_t* circ){
    if(!circ) return;
    
    vectFree(circ->pos);
    circ->pos = NULL;
    
    circ->r = 0;
}

void circSetPos(circ_t* circ, vect_t* pos){
    if(!circ || !pos) return;
    
    circ->pos = pos;
}

void circSetRadius(circ_t* circ, double radius){
    if(!circ) return;
    
    circ->r = radius;
}

void circFree(circ_t* circ){
    if(!circ) return;
    
    circInit(circ);
    free(circ);
}

bool isCircInCirc(circ_t* circInt, circ_t* circExt){
    if(!circInt || !circExt) return;
    
    // because we're lazy and efficient
    if(circInt->r > circExt->r){
        return false;
    }
    
    if(vectDist(circExt->pos, circInt->pos) < circExt->r - circInt->r){
        return true;
    }else{
        return false;
    }
}

bool isCircInGameCirc(circ_t circ){
    // TODO
    return isCircInCirc(circ, gameCirc);
}

bool isVectInCirc(vect_t* vect, circ_t* circExt){
    if(!vect || !circExt) return;
    
    circ_t* circInt = circNew();
    circSetPos(circInt, vect);
    circSetRadius(circInt, 0);
    
    return isCircInCirc(circInt, circExt);
}

bool isVectInGameCirc(vect_t vect){
    // TODO
    return isVectInCirc(vect, gameCirc);
}