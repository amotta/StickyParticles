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

// returns the sum of vectOne and vectTwo
extern vect_t vectAdd(vect_t vectOne, vect_t vectTwo);

// returns the difference of vectTwo and vectOne
extern vect_t vectSub(vect_t vectOne, vect_t vectTwo);

// returns the product of vector vect and scalar factor
extern vect_t vectScale(vect_t vect, double factor);

// returns the vector vect rotated by alpha
extern vect_t vectRotate(vect_t vect, double alpha);

// returns the length of vect
extern double vectLen(vect_t vect);

// returns the distance between start and end
extern double vectDist(vect_t start, vect_t end);

// returns the null vector
extern vect_t vectGetNull();

// returns the position of the game rectangle's center
extern vect_t getGameCenter();

#endif
