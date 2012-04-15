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

double rectGetLeft(rect_t* rect){
    if(!rect) return 0;
    
    return rect->left;
}

void rectSetLeft(rect_t* rect, double left){
    if(!rect) return;
    
    rect->left = left;
}

double rectGetRight(rect_t* rect){
    if(!rect) return 0;
    
    return rect->right;
}

void rectSetRight(rect_t* rect, double right){
    if(!rect) return;
    
    rect->right = right;
}

double rectGetBottom(rect_t* rect){
    if(!rect) return 0;
    
    return rect->bottom;
}

void rectSetBottom(rect_t* rect, double bottom){
    if(!rect) return;
    
    rect->bottom = bottom;
}

double rectGetTop(rect_t* rect){
    if(!rect) return 0;
    
    return rect->top;
}

void rectSetTop(rect_t* rect, double top){
    if(!rect) return;
    
    rect->top = top;
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