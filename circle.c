//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#include <stdbool.h>

#include "circle.h"
#include "constants.h"
#include "rectangle.h"
#include "vector.h"

circ_t gameCirc = {
    .r = RECT_Y / 2,
    .pos.x = RECT_X / 2,
    .pos.y = RECT_Y / 2
};

bool isCircInCirc(circ_t circInt, circ_t circExt){
    // because we're lazy and efficient
    if(circInt.r > circExt.r + TOL){
        return false;
    }
    
    double dist = vectLength(vectMinus(circInt.pos, circExt.pos));
    if(dist < circExt.r - circInt.r + TOL){
        return true;
    }else{
        return false;
    }
}

bool isCircInGameCirc(circ_t circ){
    return isCircInCirc(circ, gameCirc);
}

bool isCircInRect(circ_t circ, rect_t rect){
    // hiiiiigh power!
    if(
       rect.right - rect.left < circ.r
       || rect.top - rect.bottom < circ.r
    ){
        return false;
    }
    
    rect_t zone = rect;
    zone.left += circ.r;
    zone.right -= circ.r;
    zone.bottom += circ.r;
    zone.top -= circ.r;
    
    return isVectInRect(circ.pos, zone);
}

bool isCircInGameRect(circ_t circ){
    return isCircInRect(circ, gameRect);
}

bool isVectInCirc(vect_t vect, circ_t circExt){
    circ_t circInt;
    circInt.pos = vect;
    circInt.r = 0;
    
    return isCircInCirc(circInt, circExt);
}

bool isVectInGameCirc(vect_t vect){
    return isVectInCirc(vect, gameCirc);
}