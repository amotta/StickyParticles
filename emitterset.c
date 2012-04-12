//
//  emitterset.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdlib.h>

#include "emitter.h"

struct EMITTER_SET {
    unsigned int numb;
    emitter_t* set;
}

emitter_t* emitterSetNew(unsigned int numbEmitters){
    emitterSet_t* set = NULL;
    
    if((set = malloc(sizeof(emitterSet_t)))){
        set->numb = numbEmitters;
        
        if((set->set = calloc(set->numb, sizeof(emitter_t)))){
            int i;
            for(i = 0; i < set->numb; i++){
                emitterInit(&set->set[i]);
            }
        }else{
            printf("Could not allocate memory for new emitters\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Could not allocate memory for new emitter set\n");
        exit(EXIT_FAILURE);
    }
    
    return set;
}

void emitterSetFree(emitterSet_t* set){
    if(!set) return;
    
    if(set->set){
        int i;
        for(i = 0; i < set->numb; i++){
            emitterFree(&set->set[i]);
        }
        
        free(set->set);
        set->set = NULL;
    }
    
    free(set);
}
