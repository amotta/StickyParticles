//
//  groupset.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef GROUPSET_H
#define GROUPSET_H

#include <stdbool.h>

#include "group.h"

typedef struct GROUP_SET groupSet_t;

extern groupSet_t* groupSetNew();
extern void groupSetAdd(groupSet_t* set, group_t* group);
extern bool groupSetForEach(groupSet_t* set, bool (*handle)(group_t* group));
extern void groupSetMove(groupSet_t* set, double deltaT);
extern void groupSetFree(groupSet_t* set);

#endif
