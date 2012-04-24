//
//  particle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "graphics.h"
#include "particle.h"
#include "vector.h"

struct PARTICLE {
    vect_t* pos;
    part_t* next;
};

part_t* partNew(){
    part_t* part = NULL;
    
    if((part = malloc(sizeof(part_t)))){
        part->pos = NULL;
        part->next = NULL;
    }else{
        printf("Could not allocate memory for new particle\n");
        exit(EXIT_FAILURE);
    }
    
    return part;
}

vect_t* partGetPos(part_t* part){
    if(!part) return NULL;
    
    return part->pos;
}

void partSetPos(part_t* part, vect_t* pos){
    if(!part || !pos) return;
    
    part->pos = pos;
}

part_t* partGetNext(part_t* part){
    if(!part) return NULL;
    
    return part->next;
}

void partSetNext(part_t* part, part_t* next){
    if(!part) return;
    
    part->next = next;
}

bool partDraw(part_t* part){
    if(!part) return false;
    
    // HERE
    circ_t circ = {
        .pos = partGetPos(part),
        .r = R_PART
    };
    
    gfxCirc(circ, false);
    
    return true;
}

void partFree(part_t* part){
    if(!part) return;
    
    vectFree(part->pos);
    free(part);
}