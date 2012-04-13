//
//  particle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.h"

typedef struct PARTICLE part_t;

extern part_t* partNew();
extern void partInit(part_t* part);
extern void partSetPos(part_t* part, vect_t* pos);
extern void partSetNext(part_t* part, part_t* next);
extern void partFree(part_t* part);

#endif