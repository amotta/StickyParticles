//
//  particle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#include <stdlib.h>

#include "particle.h"
#include "vector.h"

struct PARTICLE {
    vect_t* pos;
    part_t* next;
};

part_t* partNew(){
    part_t* part = NULL;
    
    if((part = malloc(sizeof(part_t)))){
        partInit(part);
    }else{
        printf("Could not allocate memory for new particle\n");
        exit(EXIT_FAILURE);
    }
    
    return part;
}

void partInit(part_t* part){
    if(!part) return;
    
    vectFree(part->pos);
    part->pos = NULL;
    
    // partFree(part->next)
    part->next = NULL;
}

void partSetPos(part_t* part, vect_t* pos){
    if(!part || !pos) return;
    
    part->pos = pos;
}

void partSetNext(part_t* part, part_t* next){
    if(!part) return;
    
    part->next = next;
}

void partFree(part_t* part){
    if(!part) return;
    
    partInit(part);
}