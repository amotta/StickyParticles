//
//  groupset.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "group.h"
#include "groupset.h"

struct GROUP_SET {
    unsigned int numb;
    group_t* group;
};

groupSet_t* groupSetNew(){
    groupSet_t* set = NULL;
    
    if((set = malloc(sizeof(groupSet_t)))){
        set->numb = 0;
        set->group = NULL;
    }else{
        printf("Could not allocate memory for new group set\n");
        exit(EXIT_FAILURE);
    }
    
    return set;
}

void groupSetAdd(groupSet_t* set, group_t* group){
    if(!set || !group) return;
    
    groupSetPrev(group, NULL);
    groupSetNext(group, set->group);
    groupSetPrev(set->group, group);
    
    set->numb++;
    set->group = group;
}

bool groupSetForEach(groupSet_t* set, bool (*handle)(group_t* group)){
    group_t* cur = NULL;
    group_t* next = NULL;
    
    if(!set || !handle) return false;
    
    // init
    next = set->group;
    
    // let's dance
    while(next){
        cur = next;
        next = groupGetNext(cur);
        
        if(!handle(cur)){
            return false;
        }
    }
    
    return true;
}

void groupSetMove(groupSet_t* set, double deltaT){
    group_t* cur = NULL;
    group_t* next = NULL;
    
    if(!set) return;
    
    // init
    next = set->group;
    
    while(next){
        cur = next;
        next = groupGetNext(cur);
        
        groupMove(cur, deltaT);
    }
}

void groupSetFree(groupSet_t* set){
    if(!set) return;
    
    groupSetForEach(set, groupFree);
    free(set);
}