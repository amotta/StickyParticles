//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "circle.h"
#include "constants.h"
#include "vector.h"

struct CIRC {
    vect_t* pos;
    double r;
};

circ_t* circNew(){
    circ_t* circ = NULL;
    
    if((circ = malloc(sizeof(circ_t)))){
        circ->pos = NULL;
        circ->r = 0;
    }else{
        printf("Could not allocate memory for new circle\n");
        exit(EXIT_FAILURE);
    }
    
    return circ;
}

vect_t* circGetPos(circ_t* circ){
    if(!circ) return NULL;
    
    return circ->pos;
}

void circSetPos(circ_t* circ, vect_t* pos){
    if(!circ) return;
    
    circ->pos = pos;
}

double circGetRadius(circ_t* circ){
    if(!circ) return 0;
    
    return circ->r;
}

void circSetRadius(circ_t* circ, double radius){
    if(!circ) return;
    
    circ->r = radius;
}

void circFree(circ_t* circ){
    if(!circ) return;
    
    vectFree(circ->pos);
    free(circ);
}

circ_t* getGameCirc(){
    static circ_t* gameCirc;
    
    if(!gameCirc){
        gameCirc = circNew();
        circSetPos(gameCirc, getGameCenter());
        circSetRadius(gameCirc, RECT_Y / 2);
    }
    
    return gameCirc;
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

bool isCircInGameCirc(circ_t* circ){
    return isCircInCirc(circ, getGameCirc());
}

bool isVectInCirc(vect_t* vect, circ_t* circExt){
    static circ_t* circInt;
    bool valid;
    
    if(!vect || !circExt) return;
    
    if(!circInt){
        circInt = circNew();
        circSetRadius(circInt, 0);
    }
    
    // set circle position
    circSetPos(circInt, vect);
    
    // check
    valid = isCircInCirc(circInt, circExt);
    
    // unset pos
    circSetPos(circInt, NULL);
    
    return valid;
}

bool isVectInGameCirc(vect_t* vect){
    return isVectInCirc(vect, getGameCirc());
}