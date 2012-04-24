//
//  vector.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/6/12.
//

#include <math.h>

#include "constants.h"
#include "vector.h"

double vectLen(vect_t vect){
    return sqrt(vect.x * vect.x + vect.y * vect.y);
}

double vectDist(vect_t start, vect_t end){
    return sqrt(
        (end.x - start.x) * (end.x - start.x) 
        + (end.y - start.y) * (end.y - start.y)
    );
}

vect_t vectGetNull(){
    vect_t nullVect = {
        .x = 0,
        .y = 0
    };
    
    return nullVect;
}

vect_t getGameCenter(){
    vect_t gameCenter = {
        .x = RECT_X / 2,
        .y = RECT_Y / 2
    };
    
    return gameCenter;
}