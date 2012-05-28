//
//  group.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef GROUP_H
#define GROUP_H

#include <stdbool.h>

#include "circle.h"
#include "particle.h"
#include "vector.h"

#define GROUP_TYPE_NONE 0
#define GROUP_TYPE_HARMLESS 1
#define GROUP_TYPE_DANGEROUS 2

typedef struct GROUP group_t;

// allocate and init memory for new group
extern group_t* groupNew();

// create deep copy of group
extern group_t* groupCopy(group_t* group);

// returns the position vector of group
extern vect_t groupGetPos(group_t* group);

// changes the position vector of group to pos
extern void groupSetPos(group_t* group, vect_t pos);

// returns the speed vector of group
extern vect_t groupGetSpeed(group_t* group);

// changes the speed vector of group to speed
extern void groupSetSpeed(group_t* group, vect_t speed);

// returns the angular speed of group
extern double groupGetOmega(group_t* group);

// changes the angular speed of group to omega
extern void groupSetOmega(group_t* group, double omega);

// returns the of group. the values returned are GROUP_TYPE_NONE,
// GROUP_TYPE_HARMLESS or GROUP_TYPE_DANGEROUS
extern int groupGetType(group_t* group);

// changes the type of group to type. valid values are
// GROUP_TYPE_HARMLESS and GROUP_TYPE_DANGEROUS
extern void groupSetType(group_t* group, unsigned int type);

// returns the number of particles in group
extern unsigned int groupGetNumb(group_t* group);

// returns the pointer to the previous group of group
extern group_t* groupGetPrev(group_t* group);

// changes the pointer to the previous group of group to prev
extern void groupSetPrev(group_t* group, group_t* prev);

// returns the pointer to the next group of group
extern group_t* groupGetNext(group_t* group);

// changes the pointer to the next group of group to next
extern void groupSetNext(group_t* group, group_t* next);

// add particle part to group
extern void groupAdd(group_t* group, part_t* part);

// merge group 'from' to group 'to'
extern void groupMerge(group_t* to, group_t* from);

// applies handle to each particle of group
extern bool groupForEach(group_t* group, bool (*handle)(part_t* part));

// moves all particles of group for an interval deltaT
extern void groupMove(group_t* group, double deltaT);

// checks if particles of groupOne and groupTwo intersect
extern bool groupCheckGroup(group_t* groupOne, group_t* groupTwo);

// checks if particles of group intersect with circ
extern bool groupCheckCirc(group_t* group, circ_t circ);

// checks if particles of group intersect with borders
extern bool groupCheckBorder(group_t* group);

// draws group
extern bool groupDraw(group_t* group);

// frees group
extern bool groupFree(group_t* group);

#endif
