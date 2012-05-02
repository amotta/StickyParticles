//
//  particle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "geometry.h"
#include "graphics.h"
#include "particle.h"
#include "vector.h"

struct PARTICLE {
    vect_t pos;
    part_t* next;
};

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

int partCheckBorder(part_t* part){
    int dir = DIR_NONE;
    vect_t pos;
    
    if(!part) return dir;
    
    // init
    pos = part->pos;
    
    // TODO
    // Move in circle module
    if(pos.x < R_PART){
        dir |= DIR_LEFT;
    }
    
    if(pos.x > RECT_X - R_PART){
        dir |= DIR_RIGHT;
    }
    
    if(pos.y < R_PART){
        dir |= DIR_BOTTOM;
    }
    
    if(pos.y > RECT_Y - R_PART){
        dir |= DIR_TOP;
    }
    
    return dir;
}

bool partDraw(part_t* part){
    if(!part) return false;
    
    circ_t circ = {
        .pos = part->pos,
        .r = R_PART
    };
    
    gfxCirc(circ, false);
    
    return true;
}

bool partFree(part_t* part){
    if(!part) return false;
    
    free(part);
    
    return true;
}