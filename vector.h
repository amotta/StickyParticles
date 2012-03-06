//
//  vector.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/6/12.
//

#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double x;
    double y;
} vect_t;

extern vect_t vectMinus(vect_t vectOne, vect_t vecTwo);
extern double vectLength(vect_t vect);

#endif
