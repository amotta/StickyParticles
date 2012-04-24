//
//  rectangle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/9/12.
//

#include <stdio.h>

#include "constants.h"
#include "rectangle.h"

rect_t getGameRect(){
    static rect_t gameRect = {
        .left = 0,
        .right = RECT_X,
        .bottom = 0,
        .top = RECT_Y
    };
    
    return gameRect;
}