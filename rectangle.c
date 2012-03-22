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

const rect_t gameRect = {
    .left = 0,
    .right = RECT_X,
    .bottom = 0,
    .top = RECT_Y
};

bool isVectInRect(vect_t vect, rect_t rect){
    if(
        rect.left < vect.x && vect.x < rect.right
        && rect.bottom < vect.y && vect.y < rect.top
    ){
        return true;
    }else{
        return false;
    }
}

bool isVectInGameRect(vect_t vect){
    return isVectInRect(vect, gameRect);
}