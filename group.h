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

extern group_t* groupNew();

extern vect_t groupGetPos(group_t* group);
extern void groupSetPos(group_t* group, vect_t pos);

extern vect_t groupGetSpeed(group_t* group);
extern void groupSetSpeed(group_t* group, vect_t speed);

extern double groupGetOmega(group_t* group);
extern void groupSetOmega(group_t* group, double omega);

extern int groupGetType(group_t* group);
extern void groupSetType(group_t* group, unsigned int type);
extern unsigned int groupGetNumb(group_t* group);
extern group_t* groupGetPrev(group_t* group);
extern void groupSetPrev(group_t* group, group_t* prev);
extern group_t* groupGetNext(group_t* group);
extern void groupSetNext(group_t* group, group_t* next);

extern void groupAdd(group_t* group, part_t* part);
extern void groupMerge(group_t* to, group_t* from);
extern bool groupForEach(group_t* group, bool (*handle)(part_t* part));

extern void groupMove(group_t* group, double deltaT);
extern bool groupCheckGroup(group_t* groupOne, group_t* groupTwo);
extern bool groupCheckCirc(group_t* group, circ_t circ);
extern bool groupCheckBorder(group_t* group);

extern bool groupDraw(group_t* group);
extern bool groupFree(group_t* group);

#endif
