//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/4/12.
//

#include <math.h>

#include "circle.h"
#include "vector.h"

extern bool isCircleInCircle(circ_t circInt, circ_t circExt){
    // because we're lazy and efficient
    if(circInt.r > circExt.r){
        return false;
    }
    
    double dist = vectLength(vectMinus(circInt.pos, circExt.pos));
    
    if(dist > circExt.r - circInt.r){
        return false;
    }else{
        return true;
    }
}


