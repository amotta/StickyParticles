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

bool isCircInRect(circ_t circ, rect_t* rect){
    static rect_t* rectInt;
    
    // hiiiiigh power!
    if(
       rectGetRight(rect) - rectGetLeft(rect) < circ.r
       || rectGetTop(rect) - rectGetBottom(rect) < circ.r
    ){
        return false;
    }
    
    // set up rect
    rectSetLeft(rectInt, rectGetLeft(rect) + circ.r);
    rectSetRight(rectInt, rectGetRight(rect) - circ.r);
    rectSetBottom(rectInt, rectGetBottom(rect) + circ.r);
    rectSetTop(rectInt, rectGetTop(rect) - circ.r);
    
    return isVectInRect(circ.pos, rectInt);
}

bool isCircInGameRect(circ_t circ){
    return isCircInRect(circ, getGameRect());
}

bool isPartInGameCirc(part_t* part){
    if(!part) return;
    
    // HERE
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

bool isVectInRect(vect_t vect, rect_t* rect){
    if(!rect) return false;
    
    if(
       rectGetLeft(rect) < vect.x
       && vect.x < rectGetRight(rect)
       && rectGetBottom(rect) < vect.y
       && vect.y < rectGetTop(rect)
    ){
        return true;
    }else{
        return false;
    }
}

bool isVectInGameRect(vect_t vect){
    return isVectInRect(vect, getGameRect());
}