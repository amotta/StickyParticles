//
//  group.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "graphics.h"
#include "group.h"
#include "particle.h"
#include "vector.h"

struct GROUP {
    vect_t pos;
    vect_t speed;
    double omega;
    double momentum;
    unsigned int type;
    unsigned int numb;
    part_t* part;
    group_t* prev;
    group_t* next;
};

static part_t* groupCopyParts(group_t* group);
static void groupMergeType(group_t* to, group_t* from);
static void groupMergeMomentum(group_t* to, group_t* from);
static void groupMergeSpeed(group_t* to, group_t* from);
static void groupMergeParticles(group_t* to, group_t* from);
static void groupMergeOmega(group_t* to);

group_t* groupNew(){
    group_t* group = NULL;
    
    if((group = malloc(sizeof(group_t)))){
        group->pos = vectGetNull();
        group->speed = vectGetNull();
        group->omega = 0;
        group->momentum = 0;
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

group_t* groupCopy(group_t* group){
    group_t* copy = NULL;
    
    if(!group) return NULL;
    
    // brand new shiny group
    copy = groupNew();
    copy->pos = group->pos;
    copy->speed = group->speed;
    copy->omega = group->omega;
    copy->momentum = group->momentum;
    copy->type = group->type;
    copy->numb = group->numb;
    copy->part = groupCopyParts(group);
    
    return copy;
}

part_t* groupCopyParts(group_t* group){
    part_t* first = NULL;
    part_t* prevCopy = NULL;
    part_t* curCopy = NULL;
    part_t* curOrig = NULL;
    
    if(!group) return NULL;
    
    first = partCopy(group->part);
    
    // init
    prevCopy = first;
    curOrig = partGetNext(group->part);
    
    while(curOrig){
        curCopy = partCopy(curOrig);
        partSetNext(prevCopy, curCopy);
        
        // next
        curOrig = partGetNext(curOrig);
        prevCopy = curCopy;
    }
    
    return first;
}

vect_t groupGetPos(group_t* group){
    if(!group) return vectGetNull();
    
    return group->pos;
}

void groupSetPos(group_t* group, vect_t pos){
    if(!group) return;
    
    group->pos = pos;
}

vect_t groupGetSpeed(group_t* group){
    if(!group) return vectGetNull();
    
    return group->speed;
}

void groupSetSpeed(group_t* group, vect_t speed){
    if(!group) return;
    
    group->speed = speed;
}

double groupGetOmega(group_t* group){
    if(!group) return 0;
    
    return group->omega;
}

void groupSetOmega(group_t* group, double omega){
    part_t* cur = NULL;
    
    if(!group) return;
    
    // set new omega
    group->omega = omega;
    group->momentum = 0;
    
    // calc momentum
    vect_t curPos;
    cur = group->part;
    
    while(cur){
        curPos = vectSub(group->pos, partGetPos(cur));
        
        // calc pos x (omega x pos)
        group->momentum += curPos.x * (
            group->speed.y + group->omega * curPos.x
        );
        
        group->momentum -= curPos.y * (
            group->speed.x - group->omega * curPos.y
        );
        
        cur = partGetNext(cur);
    }
}

int groupGetType(group_t* group){
    if(!group) return GROUP_TYPE_NONE;
    
    return group->type;
}

void groupSetType(group_t* group, unsigned int type){
    if(!group) return;
    
    group->type = type;
}

unsigned int groupGetNumb(group_t* group){
    if(!group) return 0;
    
    return group->numb;
}

group_t* groupGetPrev(group_t* group){
    if(!group) return NULL;
    
    return group->prev;
}

void groupSetPrev(group_t* group, group_t* prev){
    if(!group) return;
    
    group->prev = prev;
}

group_t* groupGetNext(group_t* group){
    if(!group) return NULL;
    
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

void groupMergeType(group_t* to, group_t* from){
    if(!to || !from) return;
    
    if(
        to->type == GROUP_TYPE_DANGEROUS
        || from->type == GROUP_TYPE_DANGEROUS
    ){
        to->type = GROUP_TYPE_DANGEROUS;
    }
}

void groupMergeMomentum(group_t* to, group_t* from){
    if(!to || !from ) return;
    
    vect_t newPos;
    vect_t relPos;
    double toMomentum;
    double fromMomentum;
    double diffMomentum;
    
    // calc new position
    newPos = vectAdd(
        vectScale(to->pos, (double) to->numb / (to->numb + from->numb)),
        vectScale(from->pos, (double) from->numb / (to->numb + from->numb))
    );
    
    // calculate toMomentum
    relPos = vectSub(newPos, to->pos);
    diffMomentum = relPos.x * to->speed.y - relPos.y * to->speed.x;
    toMomentum = to->momentum + to->numb * diffMomentum;
    
    // calculate fromMomentum
    relPos = vectSub(newPos, from->pos);
    diffMomentum = relPos.x * from->speed.y - relPos.y * from->speed.x;
    fromMomentum = from->momentum + from->numb * diffMomentum;
    
    to->pos = newPos;
    to->momentum = toMomentum + fromMomentum;
}

void groupMergeSpeed(group_t* to, group_t* from){
    if(!to || !from) return;
    
    to->speed = vectAdd(
        vectScale(to->speed, (double) to->numb / (to->numb + from->numb)),
        vectScale(from->speed, (double) from->numb / (to->numb + from->numb))
    );
}

void groupMergeParticles(group_t* to, group_t* from){
    part_t* cur = NULL;
    part_t* next = NULL;
    
    if(!to || !from) return;
    
    if(to->part){
        // init
        next = to->part;
        
        // find last
        do{
            cur = next;
            next = partGetNext(cur);
        }while(next);
        
        partSetNext(cur, from->part);
    }else{
        to->part = from->part;
    }
    
    // update numbers ...
    to->numb += from->numb;
    
    // ... and pointers
    from->numb = 0;
    from->part = NULL;
}

void groupMergeOmega(group_t* to){
    part_t* cur = NULL;
    vect_t dist;
    double distSqSum;
    
    if(!to) return;
    
    // init
    distSqSum = 0;
    cur = to->part;
    
    // calc distSqSum
    while(cur){
        dist = vectSub(
            to->pos,
            partGetPos(cur)
        );
        
        // update distSqSum
        distSqSum += dist.x * dist.x + dist.y * dist.y;
        
        // next
        cur = partGetNext(cur);
    }
    
    // calc new omega
    to->omega = to->momentum / distSqSum;
}

void groupMerge(group_t* to, group_t* from){
    if(!to || !from) return;
    
    groupMergeType(to, from);
    groupMergeMomentum(to, from);
    groupMergeSpeed(to, from);
    groupMergeParticles(to, from);
    groupMergeOmega(to);
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
    part_t* cur = NULL;
    vect_t trans;
    vect_t relPos;
    
    if(!group) return;
    
    // translation
    trans = vectScale(group->speed, deltaT);

    // init
    cur = group->part;
    
    // run
    while(cur){
        // relative position
        relPos = vectSub(
            group->pos,
            partGetPos(cur)
        );
        
        // rotate if needed
        if(group->omega){
            relPos = vectRotate(
                relPos,
                group->omega * deltaT
            );
        }
        
        // set new position
        partSetPos(
            cur,
            vectAdd(group->pos,
                vectAdd(
                    relPos,
                    trans
                )
            )
        );
        
        // check out next
        cur = partGetNext(cur);
    }
    
    // update group pos
    group->pos = vectAdd(group->pos, trans);
}

bool groupCheckGroup(group_t* groupOne, group_t* groupTwo){
    part_t* partOne = NULL;
    part_t* partTwo = NULL;
    
    if(!groupOne || !groupTwo) return false;
    
    // init
    partOne = groupOne->part;
    while(partOne){
        
        // init
        partTwo = groupTwo->part;
        while(partTwo){
            if(partCheckPart(partOne, partTwo)){
                return true;
            }
            
            // next partTwo
            partTwo = partGetNext(partTwo);
        }
        
        // next partOne
        partOne = partGetNext(partOne);
    }
    
    return false;
}

bool groupCheckCirc(group_t* group, circ_t circ){
    part_t* cur = NULL;
    
    if(!group) return false;
    
    // init
    cur = group->part;
    
    while(cur){
        if(partCheckCirc(cur, circ)){
            return true;
        }
        
        cur = partGetNext(cur);
    }
    
    return false;
}

bool groupCheckBorder(group_t* group){
    int dir = DIR_NONE;
    part_t* cur = NULL;
    part_t* next = NULL;
    
    if(!group) return false;
    
    // init
    next = group->part;
    
    while(next){
        cur = next;
        next = partGetNext(cur);
        
        dir |= partCheckBorder(cur);
    }
    
    if(dir){
        group->type = GROUP_TYPE_DANGEROUS;
    }
    
    if(
        (dir & DIR_LEFT && group->speed.x < 0)
        || (dir & DIR_RIGHT && group->speed.x > 0)
    ){
        group->speed.x = - group->speed.x;
    }
    
    if(
        (dir & DIR_BOTTOM && group->speed.y < 0)
        || (dir & DIR_TOP && group->speed.y > 0)
    ){
        group->speed.y = - group->speed.y;
    }
    
    return true;
}

bool groupDraw(group_t* group){
    part_t* cur = NULL;
    part_t* next = NULL;
    
    if(!group) return false;
    
    // decide on color
    switch(group->type){
        case GROUP_TYPE_DANGEROUS:
            gfxColor(0.8, 0, 0);
            break;
        case GROUP_TYPE_HARMLESS:
            gfxColor(0, 0.8, 0);
            break;
        default:
            gfxColor(0, 0, 0);
    }
    
    // draw particles
    groupForEach(group, partDraw);
    
    return true;
}

bool groupFree(group_t* group){
    group_t* prev = NULL;
    group_t* next = NULL;
    
    if(!group) return false;
    
    // correct linking
    prev = groupGetPrev(group);
    next = groupGetNext(group);
    
    if(prev){
        groupSetNext(prev, next);
    }
    
    if(next){
        groupSetPrev(next, prev);
    }
    
    // free particles
    groupForEach(group, partFree);
    
    // free group
    free(group);
    
    return true;
}