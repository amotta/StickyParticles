//
//  vector.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/6/12.
//

#include <math.h>

#include "vector.h"

extern vect_t vectMinus(vect_t vectOne, vect_t vectTwo){
    vect_t res;
    res.x = vectOne.x - vectTwo.x;
    res.y = vectOne.y - vectTwo.y;
    
    return res;
}

extern double vectLength(vect_t vect){
    return sqrt(vect.x * vect.x + vect.y * vect.y);
}