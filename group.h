//
//  group.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef GROUP_H
#define GROUP_H

#define GROUP_TYPE_HARMLESS 1
#define GROUP_TYPE_DANGEROUS 2

typedef struct GROUP group_t;

extern group_t* groupNew();
extern void groupInit(group_t* group);
extern void groupSetPos(group_t* group, vect_t* pos);
extern void groupSetSpeed(group_t* group, vect_t* speed);
extern void groupSetOmega(group_t* group, double omega);
extern void groupSetType(group_t* group, unsigned int type);
extern void groupSetNext(group_t* group, group_t* next);
extern void groupFree(group_t* group);

#endif
