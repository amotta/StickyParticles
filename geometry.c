//
//  geometry.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/23/12.
//

#include <stdbool.h>

#include "circle.h"
#include "geometry.h"
#include "rectangle.h"

// TODO
/*
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
*/