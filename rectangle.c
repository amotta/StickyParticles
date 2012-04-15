//
//  rectangle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/9/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "rectangle.h"

struct RECT {
    double left;
    double right;
    double bottom;
    double top;
};

rect_t* rectNew(){
    rect_t* rect = NULL;
    
    if((rect = malloc(sizeof(rect_t)))){
        rect->left = 0;
        rect->right = 0;
        rect->bottom = 0;
        rect->top = 0;
    }else{
        printf("Could not allocate memory of new rectangle\n");
        exit(EXIT_FAILURE);
    }
    
    return rect;
}

void rectFree(rect_t* rect){
    if(!rect) return;
    
    free(rect);
}

rect_t* getGameRect(){
    static rect_t* gameRect;
    
    if(!gameRect){
        gameRect = rectNew();
        gameRect->left = 0;
        gameRect->right = RECT_X;
        gameRect->bottom = 0;
        gameRect->top = RECT_Y;
    }
    
    return gameRect;
}

// TODO
/*
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
*/