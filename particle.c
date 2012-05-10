//
//  particle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "circle.h"
#include "constants.h"
#include "geometry.h"
#include "graphics.h"
#include "particle.h"
#include "vector.h"

struct PARTICLE {
    vect_t pos;
    part_t* next;
};

static inline circ_t partGetCirc(part_t* part);

part_t* partNew(){
    part_t* part = NULL;
    
    if((part = malloc(sizeof(part_t)))){
        part->pos = vectGetNull();
        part->next = NULL;
    }else{
        printf("Could not allocate memory for new particle\n");
        exit(EXIT_FAILURE);
    }
    
    return part;
}

vect_t partGetPos(part_t* part){
    if(!part) return vectGetNull();
    
    return part->pos;
}

void partSetPos(part_t* part, vect_t pos){
    if(!part) return;
    
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

bool partCheckPart(part_t* partOne, part_t* partTwo){
    if(!partOne || !partTwo) return false;
    
    return circCheckCirc(
        partGetCirc(partOne),
        partGetCirc(partTwo)
    );
}

int partCheckBorder(part_t* part){
    if(!part) return DIR_NONE;
    
    return circCheckBorder(partGetCirc(part));
}

bool partCheckCirc(part_t* part, circ_t circ){
    if(!part) return false;
    
    return circCheckCirc(partGetCirc(part), circ);
}

bool partDraw(part_t* part){
    if(!part) return false;
    
    gfxCirc(partGetCirc(part), false);
    
    return true;
}

bool partFree(part_t* part){
    if(!part) return false;
    
    free(part);
    
    return true;
}

circ_t partGetCirc(part_t* part){
    static circ_t circ = { .r = R_PART };
    
    if(!part) return circGetNull();
    
    // prepare circ
    circ.pos = part->pos;
    
    return circ;
}