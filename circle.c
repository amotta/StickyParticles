//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/7/12.
//

#include "circle.h"
#include "constants.h"
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