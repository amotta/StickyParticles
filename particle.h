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

// allocates and inits a new particle
extern part_t* partNew();

// creates a deep copy of part
extern part_t* partCopy(part_t* part);

// returns the position of part
extern vect_t partGetPos(part_t* part);

// changes the position of part to pos
extern void partSetPos(part_t* part, vect_t pos);

// returns pointer to next particle of part
extern part_t* partGetNext(part_t* part);

// changes the pointer to the next particle of part to next
extern void partSetNext(part_t* part, part_t* next);

// checks if partOne and partTwo intersect
extern bool partCheckPart(part_t* partOne, part_t* partTwo);

// checks if part touches on of the borders.
// returns DIR_LEFT, DIR_RIGHT, DIR_BOTTOM, DIR TOP or DIR_NONE
extern int partCheckBorder(part_t* part);

// checks if part intersects with circ
extern bool partCheckCirc(part_t* part, circ_t circ);

// draws part
extern bool partDraw(part_t* part);

// frees part
extern bool partFree(part_t* part);

#endif
