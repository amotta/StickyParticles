//
//  particleset.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#include "particle.h"
#include "particleset.h"

struct PART_SET {
    unsigned int numb;
    part_t* first;
};

partSet_t* partSetNew(){
    partSet_t* set = NULL;
}

void partSetAdd(partSet_t* set, part_t* part){
    if(!set || !part) return;
    
    partSetNext(part, set->first);
    
    set->numb++;
    set->first = part;
}

void partSetFree(partSet_t* set){
    if(!set) return;
    
    part_t* cur = NULL;
    part_t* next = set->first;
    
    while(next){
        cur = next;
        next = partGetNext(cur);
        
        partFree(cur);
    }
    
    set->first = NULL;
}

