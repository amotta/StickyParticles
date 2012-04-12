//
//  groupset.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef GROUPSET_H
#define GROUPSET_H

#include "group.h"

typedef struct GROUP_SET groupSet_t;

groupSet_t* groupSetNew();
void groupSetAdd(groupSet_t* set, group_t* group);
void groupSetFree(groupSet_t* set);

#endif
