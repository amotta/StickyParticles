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

extern double vectLen(vect_t vect);
extern double vectDist(vect_t start, vect_t end);

extern vect_t getGameCenter();

#endif
