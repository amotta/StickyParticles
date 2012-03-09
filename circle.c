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

extern bool isCircInCirc(circ_t circInt, circ_t circExt){
    // because we're lazy and efficient
    if(circInt.r > circExt.r){
        return false;
    }
    
    double dist = vectLength(vectMinus(circInt.pos, circExt.pos));
    if(dist < circExt.r - circInt.r){
        return true;
    }else{
        return false;
    }
}

extern bool isCircInGameCirc(circ_t circ){
    static circ_t gameCirc;
    static bool gameCircInit;
    
    // init gameCirc if needed
    if(!gameCircInit){
        gameCirc.pos.x = RECT_X / 2;
        gameCirc.pos.y = RECT_Y / 2;
        gameCirc.r = RECT_Y / 2;
        
        gameCircInit = true;
    }
    
    return isCircInCirc(circ, gameCirc);
}

extern bool isCircInRect(circ_t circ, rect_t rect){
    // hiiiiigh power!
    if(
       rect.right - rect.left < circ.r
       || rect.top - rect.bottom < circ.r
    ){
        return false;
    }
    
    if(
       circ.pos.x > rect.left + circ.r
       && circ.pos.x < rect.right - circ.r
       && circ.pos.y > rect.bottom + circ.r
       && circ.pos.y < rect.top - circ.r
       ){
        return true;
    }else{
        return false;
    }
}