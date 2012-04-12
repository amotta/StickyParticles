//
//  group.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdlib.h>

#include "group.h"
#include "vector.h"

struct GROUP {
    vect_t* pos;
    vect_t* speed;
    
    double omega;
    unsigned int type;
    unsigned int numbParts;
    
    group_t* next;
};

group_t* groupNew(){
    group_t* group = NULL;
    
    if((group = malloc(sizeof(group_t)))){
        groupInit(group);
    }else{
        printf("Could not allocate memory for new group\n");
        exit(EXIT_FAILURE);
    }
    
    return group;
}

void groupInit(group_t* group){
    if(!group){
        return;
    }
    
    vectFree(group->pos);
    group->pos = NULL;
    
    vectFree(group->speed);
    group->speed = NULL;
    
    group->omega = 0;
    group->type = 0;
    group->numbParts = 0;
    
    // groupFree(group->next);
    group->next = NULL;
}

void groupSetPos(group_t* group, vect_t* pos){
    if(!group || !pos) return;
    
    group->pos = pos;
}

void groupSetSpeed(group_t* group, vect_t* speed){
    if(!group || !speed) return;
    
    group->speed = speed;
}

void groupSetOmega(group_t* group, double omega){
    if(!group) return;
    
    group->omega = omega;
}

void groupSetType(group_t* group, unsigned int type){
    if(!group) return;
    
    group->type = type;
}

void groupSetNext(group_t* group, group_t* next){
    if(!group) return;
    
    group->next = next;
}

void groupFree(group_t* group){
    if(!group){
        return;
    }
    
    groupInit(group);
    free(group);
}