//
//  emitterset.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "emitter.h"
#include "emitterset.h"
#include "groupset.h"

struct EMITTER_SET {
    unsigned int numb;
    emitter_t** set;
};

emitterSet_t* emitterSetNew(unsigned int numbEmitters){
    emitterSet_t* set = NULL;
    
    if((set = malloc(sizeof(emitterSet_t)))){
        set->numb = numbEmitters;
        
        // TODO
        // Improve
        if((set->set = malloc(numbEmitters * sizeof(emitter_t*)))){
            unsigned int i;
            for(i = 0; i < set->numb; i++){
                set->set[i] = emitterNew();
            }
        }else{
            printf("Could not allocate memory for new emitter set\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Could not allocate memory for new emitter set\n");
        exit(EXIT_FAILURE);
    }
    
    return set;
}

groupSet_t* emitterSetEmit(emitterSet_t* set, double deltaT){
    group_t* newGroup = NULL;
    groupSet_t* newGroups = NULL;
    
    if(!set || !set->set) return newGroups;
    
    unsigned int i;
    for(i = 0; i < set->numb; i++){
        newGroup = emitterEmit(set->set[i], deltaT);
        
        if(newGroup){
            if(!newGroups){
                newGroups = groupSetNew();
            }
            
            groupSetAdd(newGroups, newGroup);
        }
    }
    
    return newGroups;
}

bool emitterSetForEach(emitterSet_t* set, bool (*handle)(emitter_t* emitter)){
    if(!set || !handle) return false;
    
    unsigned int i;
    for(i = 0; i < set->numb; i++){
        if(!handle(set->set[i])){
            return false;
        }
    }
    
    return true;
}

void emitterSetFree(emitterSet_t* set){
    if(!set || !set->set) return;
    
    unsigned int i;
    for(i = 0; i < set->numb; i++){
        emitterFree(set->set[i]);
        set->set[i] = NULL;
    }
        
    free(set->set);
    set->set = NULL;
    
    free(set);
}
