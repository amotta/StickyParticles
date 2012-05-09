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

void groupSetMerge(groupSet_t* to, groupSet_t* from){
    group_t* cur = NULL;
    group_t* next = NULL;
    
    if(!to || !from) return;
    
    if(to->group){
        // find last
        cur = to->group;
        next = groupGetNext(cur);
        
        while(next){
            cur = next;
            next = groupGetNext(cur);
        }
        
        groupSetNext(cur, from->group);
        groupSetPrev(from->group, cur);
    }else{
        to->group = from->group;
    }
    
    // update numbers ...
    to->numb += from->numb;
    
    // ... and pointers
    from->numb = 0;
    from->group = NULL;
    
    // free from
    groupSetFree(from);
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

void groupSetCollide(groupSet_t* set){
    group_t* groupOne = NULL;
    group_t* groupOneNext = NULL;
    group_t* groupTwo = NULL;
    group_t* groupTwoNext = NULL;
    
    if(!set) return;
    
    // groupOne
    groupOne = set->group;
    while(groupOne){
        groupOneNext = groupGetNext(groupOne);
        
        // groupTwo
        groupTwo = groupGetNext(groupOne);
        while(groupTwo){
            groupTwoNext = groupGetNext(groupTwo);
            
            // check for collision
            if(groupCheckGroup(groupOne, groupTwo)){
                if(
                    groupGetType(groupOne) == GROUP_TYPE_DANGEROUS
                    && groupGetType(groupTwo) == GROUP_TYPE_DANGEROUS
                ){
                    // correct groupOneNext
                    if(groupOneNext == groupTwo){
                        groupOneNext = groupTwoNext;
                    }
                    
                    // correct set->group
                    if(set->group == groupOne){
                        set->group = groupOneNext;
                    }
                    
                    // free first group
                    groupFree(groupOne);
                    groupOne = NULL;
                    
                    // free second group
                    groupFree(groupTwo);
                    groupTwo = NULL;
                    
                    // update number of groups
                    set->numb = set->numb - 2;
                    
                    break;
                }else{
                    // merge groups
                    groupMerge(groupOne, groupTwo);
                    groupFree(groupTwo);
                    groupTwo = NULL;
                    
                    // update number of groups
                    set->numb = set->numb - 1;
                }
            }
            
            // go to next
            groupTwo = groupTwoNext;
        }
        
        groupOne = groupOneNext;
    }
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