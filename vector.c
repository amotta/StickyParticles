//
//  vector.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/6/12.
//

#include <math.h>

#include "constants.h"
#include "vector.h"

vect_t vectAdd(vect_t vectOne, vect_t vectTwo){
    vect_t sum = {
        .x = vectOne.x + vectTwo.x,
        .y = vectOne.y + vectTwo.y,
        .z = vectOne.z + vectTwo.z
    };
    
    return sum;
}

vect_t vectSub(vect_t vectOne, vect_t vectTwo){
    vect_t diff = {
        .x = vectTwo.x - vectOne.x,
        .y = vectTwo.y - vectOne.y,
        .z = vectTwo.z - vectOne.z
    };
    
    return diff;
}

vect_t vectMul(vect_t vectOne, vect_t vectTwo){
    vect_t res = {
        .x = vectOne.y * vectTwo.z - vectOne.z * vectTwo.y,
        .y = vectOne.z * vectTwo.x - vectOne.x * vectTwo.z,
        .z = vectOne.x * vectTwo.y - vectOne.y * vectTwo.x
    };
    
    return res;
}

vect_t vectScale(vect_t vect, double factor){
    vect_t res = {
        .x = vect.x * factor,
        .y = vect.y * factor,
        .z = vect.z * factor
    };
    
    return res;
}

vect_t vectRotate(vect_t vect, double alpha){
    double curCos = cos(alpha);
    double curSin = sin(alpha);
    
    vect_t res = {
        .x = vect.x * curCos - vect.y * curSin,
        .y = vect.x * curSin + vect.y * curCos,
        .z = vect.z
    };
    
    return res;
}

double vectLen(vect_t vect){
    return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}

double vectDist(vect_t start, vect_t end){
    return vectLen(vectSub(end, start));
}

vect_t vectGetNull(){
    vect_t nullVect = {
        .x = 0,
        .y = 0,
        .z = 0
    };
    
    return nullVect;
}

vect_t getGameCenter(){
    vect_t gameCenter = {
        .x = RECT_X / 2,
        .y = RECT_Y / 2,
        .z = 0
    };
    
    return gameCenter;
}