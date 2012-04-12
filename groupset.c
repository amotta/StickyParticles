//
//  groupset.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include "group.h"
#include "groupset.h"

struct GROUP_SET {
    unsigned int numb;
    group_t* first;
};

groupSet_t* groupSetNew(){
    groupSet_t* set = NULL;
    
    if((set = malloc(sizeof(groupSet_t)))){
        set->numb = 0;
        set->first = NULL;
    }else{
        printf("Could not allocate memory for new group set\n");
        exit(EXIT_FAILURE);
    }
    
    return set;
}

void groupSetAdd(groupSet_t* set, group_t* group){
    if(!set || !group) return;
    
    groupSetNext(group, set->first);
    
    set->numb++;
    set->first = group;
}

// TODO
void groupSetFree(groupSet_t* set){
    if(!set) return;
}