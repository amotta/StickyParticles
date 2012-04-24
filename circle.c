//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#include "circle.h"
#include "constants.h"
#include "vector.h"

circ_t getGameCirc(){
    static circ_t gameCirc = {
        .pos = {
            .x = RECT_X / 2,
            .y = RECT_Y / 2
        },
        .r = RECT_Y / 2
    };
    
    return gameCirc;
}

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