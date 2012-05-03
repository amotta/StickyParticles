//
//  group.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef GROUP_H
#define GROUP_H

#include <stdbool.h>

#include "particle.h"
#include "vector.h"

#define GROUP_TYPE_HARMLESS 1
#define GROUP_TYPE_DANGEROUS 2

typedef struct GROUP group_t;

extern group_t* groupNew();
extern void groupSetPos(group_t* group, vect_t pos);
extern void groupSetSpeed(group_t* group, vect_t speed);
extern void groupSetOmega(group_t* group, double omega);
extern void groupSetType(group_t* group, unsigned int type);
extern group_t* groupGetPrev(group_t* group);
extern void groupSetPrev(group_t* group, group_t* prev);
extern group_t* groupGetNext(group_t* group);
extern void groupSetNext(group_t* group, group_t* next);
extern void groupAdd(group_t* group, part_t* part);
extern bool groupForEach(group_t* group, bool (*handle)(part_t* part));
extern void groupMove(group_t* group, double deltaT);
extern bool groupCheckBorder(group_t* group);
extern bool groupDraw(group_t* group);
extern bool groupFree(group_t* group);

#endif
