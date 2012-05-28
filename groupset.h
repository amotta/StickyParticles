//
//  groupset.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef GROUPSET_H
#define GROUPSET_H

#include <stdbool.h>

#include "circle.h"
#include "group.h"

typedef struct GROUP_SET groupSet_t;

// allocates and inits memory for new groupSet
extern groupSet_t* groupSetNew();

// creates deep copy of set
extern groupSet_t* groupSetCopy(groupSet_t* set);

// returns the number of groups contained in set
extern unsigned int groupSetGetNumb(groupSet_t* set);

// adds group to set
extern void groupSetAdd(groupSet_t* set, group_t* group);

// deletes group from set and frees group
extern void groupSetDel(groupSet_t* set, group_t* group);

// adds all groups from set 'from' to set 'to'
extern void groupSetMerge(groupSet_t* to, groupSet_t* from);

// applies handle to each group of set
extern bool groupSetForEach(groupSet_t* set, bool (*handle)(group_t* group));

// checks all associated groups against each other for collision
// and reacts to them
extern void groupSetCollide(groupSet_t* set);

// checks all associated groups against collision with disc.
// returns the number of groups collected or a negative number
// if disc touched a dangerous group
extern int groupSetCheckDisc(groupSet_t* set, circ_t disc);

// moves all associated groups
extern void groupSetMove(groupSet_t* set, double deltaT);

// frees set and all associated groups
extern void groupSetFree(groupSet_t* set);

#endif
