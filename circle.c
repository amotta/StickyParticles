//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#include <math.h>
#include <stdbool.h>

#include "circle.h"
#include "constants.h"
#include "geometry.h"
#include "vector.h"

bool isCircInCirc(circ_t circInt, circ_t circExt){
    // because we're lazy and efficient
    if(circInt.r > circExt.r){
        return false;
    }
    
    if(vectDist(circExt.pos, circInt.pos) < circExt.r - circInt.r){
        return true;
    }else{
        return false;
    }
}

bool isCircInGameCirc(circ_t circ){
    return isCircInCirc(circ, getGameCirc());
}

bool circCheckCirc(circ_t circOne, circ_t circTwo){
    if(
       fabs(circOne.pos.x - circTwo.pos.x) > circOne.r + circTwo.r
       || fabs(circOne.pos.y - circTwo.pos.y) > circOne.r + circTwo.r
    ){
        return false;
    }
    
    if(vectDist(circOne.pos, circTwo.pos) > circOne.r + circTwo.r){
        return false;
    }else{
        return true;
    }
}

int circCheckBorder(circ_t circ){
    int dir = DIR_NONE;
    
    if(circ.pos.x < circ.r){
        dir |= DIR_LEFT;
    }
    
    if(circ.pos.x > RECT_X - circ.r){
        dir |= DIR_RIGHT;
    }
    
    if(circ.pos.y < circ.r){
        dir |= DIR_BOTTOM;
    }
    
    if(circ.pos.y > RECT_Y - circ.r){
        dir |= DIR_TOP;
    }
    
    return dir;
}

circ_t circProjectOnCirc(circ_t from, circ_t to){
    vect_t dir;
    vect_t diff;
    double alpha;
    
    // calculate direction
    diff = vectSub(to.pos, from.pos);
    alpha = atan2(diff.y, diff.x);
    
    // calculate position on border
    dir.x = (to.r - from.r) * cos(alpha);
    dir.y = (to.r - from.r) * sin(alpha);
    
    // set new position
    from.pos = vectAdd(to.pos, dir);
    
    return from;
}

circ_t circGetNull(){
    circ_t nullCirc = {
        .pos = vectGetNull(),
        .r = 0
    };
    
    return nullCirc;
}

circ_t getGameCirc(){
    circ_t gameCirc = {
        .pos = getGameCenter(),
        .r = RECT_Y / 2
    };
    
    return gameCirc;
}