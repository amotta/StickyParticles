//
//  particle.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdbool.h>

#include "vector.h"

typedef struct PARTICLE part_t;

extern part_t* partNew();
extern vect_t partGetPos(part_t* part);
extern void partSetPos(part_t* part, vect_t pos);
extern part_t* partGetNext(part_t* part);
extern void partSetNext(part_t* part, part_t* next);
extern bool partCheckPart(part_t* partOne, part_t* partTwo);
extern int partCheckBorder(part_t* part);
extern bool partCheckCirc(part_t* part, circ_t circ); 
extern bool partDraw(part_t* part);
extern bool partFree(part_t* part);

#endif
