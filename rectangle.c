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

extern bool isVectInRect(vect_t vect, rect_t rect){
    if(
        rect.left < vect.x && vect.x < rect.right
        && rect.bottom < vect.y && vect.y < rect.top
    ){
        return true;
    }else{
        return false;
    }
}

extern bool isVectInGameRect(vect_t vect){
    static rect_t gameRect;
    static bool gameRectInit;
    
    if(!gameRectInit){
        gameRect.left = 0;
        gameRect.right = RECT_X;
        gameRect.bottom = 0;
        gameRect.top = RECT_Y;
        
        gameRectInit = true;
    }
    
    return isVectInRect(vect, gameRect);
}