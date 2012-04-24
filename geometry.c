//
//  geometry.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/23/12.
//

#include <stdbool.h>
#include <stdlib.h>

#include "circle.h"
#include "constants.h"
#include "geometry.h"
#include "particle.h"
#include "rectangle.h"
#include "vector.h"

bool isCircInRect(circ_t circ, rect_t rect){
    // hiiiiigh power!
    if(
       rect.right - rect.left < circ.r
       || rect.top - rect.bottom < circ.r
    ){
        return false;
    }
    
    rect_t rectInt = {
        .left = rect.left + circ.r,
        .right = rect.right - circ.r,
        .bottom = rect.bottom + circ.r,
        .top = rect.top - circ.r
    };
    
    return isVectInRect(circ.pos, rectInt);
}

bool isCircInGameRect(circ_t circ){
    return isCircInRect(circ, getGameRect());
}

bool isPartInGameCirc(part_t* part){
    if(!part) return;
    
    circ_t circ = {
        .pos = partGetPos(part),
        .r = R_PART
    };
    
    return isCircInGameCirc(circ);
}

bool isPartInGameRect(part_t* part){
    if(!part) return;
    
    circ_t circ = {
        .pos = partGetPos(part),
        .r = R_PART
    };
    
    return isCircInGameRect(circ);
}

bool isVectInCirc(vect_t vect, circ_t circExt){
    circ_t circInt = {
        .pos = vect,
        .r = 0
    };
    
    return isCircInCirc(circInt, circExt);
}

bool isVectInGameCirc(vect_t vect){
    return isVectInCirc(vect, getGameCirc());
}

bool isVectInRect(vect_t vect, rect_t rect){
    if(
       rect.left < vect.x
       && vect.x < rect.right
       && rect.bottom < vect.y
       && vect.y < rect.top
    ){
        return true;
    }else{
        return false;
    }
}

bool isVectInGameRect(vect_t vect){
    return isVectInRect(vect, getGameRect());
}