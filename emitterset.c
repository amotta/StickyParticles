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

struct EMITTER_SET {
    unsigned int numb;
    emitter_t** set;
};

emitterSet_t* emitterSetNew(unsigned int numbEmitters){
    emitterSet_t* set = NULL;
    
    if((set = malloc(sizeof(emitterSet_t)))){
        set->numb = numbEmitters;
        
        int i;
        for(i = 0; i < set->numb; i++){
            set->set[i] = emitterNew();
        }
    }else{
        printf("Could not allocate memory for new emitter set\n");
        exit(EXIT_FAILURE);
    }
    
    return set;
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
    if(!set) return;
    
    // TODO
    // emitterSetForEach(set, emitterFree);
    
    if(set->set){
        int i;
        for(i = 0; i < set->numb; i++){
            emitterFree(set->set[i]);
            set->set[i] = NULL;
        }
        
        set->set = NULL;
    }
    
    free(set);
}
