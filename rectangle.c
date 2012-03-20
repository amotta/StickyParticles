//
//  rectangle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/9/12.
//

#include <stdbool.h>

#include "constants.h"
#include "rectangle.h"
#include "vector.h"

rect_t gameRect = {
    .left = 0,
    .right = RECT_X,
    .bottom = 0,
    .top = RECT_Y
};

bool isVectInRect(vect_t vect, rect_t rect){
    if(
        rect.left < vect.x + TOL && vect.x < rect.right - TOL
        && rect.bottom < vect.y + TOL && vect.y < rect.top - TOL
    ){
        return true;
    }else{
        return false;
    }
}

bool isVectInGameRect(vect_t vect){
    return isVectInRect(vect, gameRect);
}