//
//  groupset.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "circle.h"
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

groupSet_t* groupSetCopy(groupSet_t* set){
    group_t* prevCopy = NULL;
    group_t* curCopy = NULL;
    group_t* curOrig = NULL;
    groupSet_t* copy = NULL;
    
    if(!set) return NULL;
    
    // new empty set
    copy = groupSetNew();
    copy->numb = set->numb;
    
    if(set->group){
        copy->group = groupCopy(set->group);
        
        // init
        prevCopy = copy->group;
        curOrig = groupGetNext(set->group);
        
        // copy every group
        while(curOrig){
            curCopy = groupCopy(curOrig);
            groupSetPrev(curCopy, prevCopy);
            groupSetNext(prevCopy, curCopy);
            
            // next
            curOrig = groupGetNext(curOrig);
            prevCopy = curCopy;
        }
    }else{
        copy->group = NULL;
    }
    
    return copy;
}

unsigned int groupSetGetNumb(groupSet_t* set){
    if(!set) return 0;
    
    return set->numb;
}

void groupSetAdd(groupSet_t* set, group_t* group){
    if(!set || !group) return;
    
    groupSetPrev(group, NULL);
    groupSetNext(group, set->group);
    groupSetPrev(set->group, group);
    
    set->numb++;
    set->group = group;
}

void groupSetDel(groupSet_t* set, group_t* group){
    if(!set || !group) return;
    
    // correct pointer
    if(set->group == group){
        set->group = groupGetNext(group);
    }
    
    // free group
    groupFree(group);
    group = NULL;
    
    // correct number
    set->numb--;
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
    
    bool groupOneMixed;
    bool groupOneMerged;
    unsigned int groupOneType;
    
    // groupOne
    groupOne = set->group;
    while(groupOne){
        groupOneNext = groupGetNext(groupOne);
        
        groupOneMixed = false;
        groupOneMerged = false;
        groupOneType = groupGetType(groupOne);
        
        // groupTwo
        groupTwo = groupGetNext(groupOne);
        while(groupTwo){
            groupTwoNext = groupGetNext(groupTwo);
            
            // check for collision
            if(groupCheckGroup(groupOne, groupTwo)){
                // correct groupOneNext
                if(groupOneNext == groupTwo){
                    groupOneNext = groupTwoNext;
                }
                
                // is groupOne mixed?
                if(groupOneType != groupGetType(groupTwo)){
                    groupOneMixed = true;
                }
                
                groupMerge(groupOne, groupTwo);
                groupOneMerged = true;
                
                groupSetDel(set, groupTwo);
                groupTwo = NULL;
                
            }
            
            // go to next
            groupTwo = groupTwoNext;
        }
        
        // delete group when only dangerous groups were merged
        if(
            groupOneMerged
            && groupOneType == GROUP_TYPE_DANGEROUS
            && !groupOneMixed
        ){
            groupSetDel(set, groupOne);
            groupOne = NULL;
        }
        
        groupOne = groupOneNext;
    }
}

int groupSetCheckDisc(groupSet_t* set, circ_t disc){
    int out = 0;
    group_t* cur = NULL;
    group_t* next = NULL;
    
    if(!set) return -1;
    
    // init
    next = set->group;
    
    while(next){
        cur = next;
        next = groupGetNext(cur);
        
        if(groupCheckCirc(cur, disc)){
            switch(groupGetType(cur)){
                case GROUP_TYPE_HARMLESS:
                    // add points
                    out += groupGetNumb(cur);
                    
                    // free group
                    groupSetDel(set, cur);
                    cur = NULL;
                    break;
                default:
                    return -1;
            }
        }
    }
    
    return out;
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