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

extern vect_t vectAdd(vect_t vectOne, vect_t vectTwo);
extern vect_t vectSub(vect_t vectOne, vect_t vectTwo);
extern vect_t vectMul(vect_t vect, double factor);
extern double vectLen(vect_t vect);
extern double vectDist(vect_t start, vect_t end);

extern vect_t vectGetNull();
extern vect_t getGameCenter();

#endif
