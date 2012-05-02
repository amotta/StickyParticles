//
//  group.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "group.h"
#include "particle.h"
#include "vector.h"

struct GROUP {
    vect_t pos;
    vect_t speed;
    double omega;
    unsigned int type;
    unsigned int numb;
    part_t* part;
    group_t* prev;
    group_t* next;
};

group_t* groupNew(){
    group_t* group = NULL;
    
    if((group = malloc(sizeof(group_t)))){
        group->pos = vectGetNull();
        group->speed = vectGetNull();
        group->omega = 0;
        group->type = 0;
        group->numb = 0;
        group->part = NULL;
        group->prev = NULL;
        group->next = NULL;
    }else{
        printf("Could not allocate memory for new group\n");
        exit(EXIT_FAILURE);
    }
    
    return group;
}

void groupSetPos(group_t* group, vect_t pos){
    if(!group) return;
    
    group->pos = pos;
}

void groupSetSpeed(group_t* group, vect_t speed){
    if(!group) return;
    
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

group_t* groupGetPrev(group_t* group){
    if(!group) return;
    
    return group->prev;
}

void groupSetPrev(group_t* group, group_t* prev){
    if(!group) return;
    
    group->prev = prev;
}

group_t* groupGetNext(group_t* group){
    if(!group) return;
    
    return group->next;
}

void groupSetNext(group_t* group, group_t* next){
    if(!group) return;
    
    group->next = next;
}

void groupAdd(group_t* group, part_t* part){
    if(!group || !part) return;
    
    // set next
    partSetNext(part, group->part);
    
    group->part = part;
    group->numb++;
}

bool groupForEach(group_t* group, bool (*handle)(part_t* part)){
    part_t* cur = NULL;
    part_t* next = NULL;
    
    if(!group || !handle) return false;
    
    // init
    next = group->part;
    
    // run
    while(next){
        cur = next;
        next = partGetNext(cur);
        
        if(!handle(cur)){
            return false;
        }
    }
    
    return true;
}

void groupMove(group_t* group, double deltaT){
    vect_t diff;
    vect_t newPos;
    part_t* cur = NULL;
    part_t* next = NULL;
    
    if(!group) return;
    
    // group dislocation
    diff = vectMul(group->speed, deltaT);

    // init
    next = group->part;
    
    // run
    while(next){
        cur = next;
        next = partGetNext(cur);
        
        partSetPos(
            cur,
            vectAdd(
                diff,
                partGetPos(cur)
            )
        );
    }
    
    // update group pos
    group->pos = vectAdd(group->pos, diff);
}

bool groupDraw(group_t* group){
    part_t* cur = NULL;
    part_t* next = NULL;
    
    if(!group) return false;
    
    // decide on color
    if(group->type == GROUP_TYPE_DANGEROUS){
        gfxColor(0.8, 0, 0);
    }else{
        gfxColor(0, 0.8, 0);
    }
    
    // draw particles
    groupForEach(group, partDraw);
    
    return true;
}

bool groupFree(group_t* group){
    if(!group) false;
    
    groupForEach(group, partFree);
    free(group);
    
    return true;
}