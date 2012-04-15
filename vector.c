//
//  vector.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/6/12.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "vector.h"

struct VECT {
    double x;
    double y;
};

vect_t* vectNew(){
    vect_t* vect = NULL;
    
    if(vect = malloc(sizeof(vect_t))){
        vect->x = 0;
        vect->y = 0;
    }else{
        printf("Could not allocate memory for new vector\n");
        exit(EXIT_FAILURE);
    }
    
    return vect;
}

void vectSet(vect_t* vect, double x, double y){
    if(!vect) return;
    
    vect->x = x;
    vect->y = y;
}

double vectGetX(vect_t* vect){
    if(!vect) return 0;
    
    return vect->x;
}

double vectGetY(vect_t* vect){
    if(!vect) return 0;
    
    return vect->y;
}

double vectLen(vect_t* vect){
    if(!vect) return 0;
    
    return sqrt(vect->x * vect->x + vect->y * vect->y);
}

double vectDist(vect_t* start, vect_t* end){
    return sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2));
}

void vectFree(vect_t* vect){
    if(!vect) return;
    
    free(vect);
}

vect_t* getGameCenter(){
    static vect_t* gameCenter;
    
    if(!gameCenter){
        gameCenter = vectNew();
        vectSet(gameCenter, RECT_X / 2, RECT_Y / 2);
    }
    
    return gameCenter;
}