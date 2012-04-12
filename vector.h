//
//  vector.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/6/12.
//

#ifndef VECTOR_H
#define VECTOR_H

typedef struct VECT vect_t;

extern vect_t* vectNew();
extern void vectSet(vect_t* vect, double x, double y);
extern double vectDisc(vect_t* start, vect_t* end);
extern void vectFree(vect_t* vect);

#endif
