//
//  emitter.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "emitter.h"
#include "graphics.h"
#include "groupset.h"
#include "rectangle.h"
#include "vector.h"

#define EMITTER_SIZE 0.1
#define MAX_EMITTER_LEN 1.0

struct EMITTER {
    vect_t pos;
    double angle;
    double alpha;
    double flow;
    double speed;
};

emitter_t* emitterNew(){
    emitter_t* emitter = NULL;
    
    if((emitter = malloc(sizeof(emitter_t)))){
        emitter->pos = vectGetNull();
        emitter->angle = 0;
        emitter->alpha = 0;
        emitter->flow = 0;
        emitter->speed = 0;
    }else{
        printf("Could not allocate memory for new emitter\n");
        exit(EXIT_FAILURE);
    }
    
    return emitter;
}

vect_t emitterGetPos(emitter_t* emitter){
    if(!emitter) return vectGetNull();
    
    return emitter->pos;
}

void emitterSetPos(emitter_t* emitter, vect_t pos){
    vect_t gameCenter;
    double diffX, diffY;
    
    if(!emitter) return;
    
    // set pos
    emitter->pos = pos;
    
    // update angle
    gameCenter = getGameCenter();
    diffX = pos.x - gameCenter.x;
    diffY = pos.y - gameCenter.y;
    
    emitter->angle = atan2(diffY, diffX) + M_PI;
}

double emitterGetAngle(emitter_t* emitter){
    if(!emitter) return 0;
    
    return emitter->angle;
}

double emitterGetAlpha(emitter_t* emitter){
    if(!emitter) return 0;
    
    return emitter->alpha;
}

void emitterSetAlpha(emitter_t* emitter, double alpha){
    if(!emitter) return;
    
    emitter->alpha = alpha;
}

void emitterSetFlow(emitter_t* emitter, double flow){
    if(!emitter) return;
    
    emitter->flow = flow;
}

double emitterGetSpeed(emitter_t* emitter){
    if(!emitter) return 0;
    
    return emitter->speed;
}

void emitterSetSpeed(emitter_t* emitter, double speed){
    if(!emitter) return;
    
    emitter->speed = speed;
}

groupSet_t* emitterEmit(emitter_t* emitter, double deltaT){
    part_t* part = NULL;
    group_t* group = NULL;
    groupSet_t* groups = NULL;
    
    if(!emitter) return groups;
    
    // init
    groups = groupSetNew();
    
    // generate random number
    double random = (double) rand() / RAND_MAX;
    unsigned int numbParts = deltaT * emitter->flow / random;
    
    vect_t speed;
    double speedAngle;
    
    // TODO
    // Only one group for each emitter and update
    unsigned int i;
    for(i = 0; i < numbParts; i++){
        part = partNew();
        partSetPos(part, emitter->pos);
        
        group = groupNew();
        groupSetPos(group, emitter->pos);
        
        // calculate speed
        speedAngle = emitter->alpha * (1.0 - 2.0 * rand() / RAND_MAX);
        speed.x = emitter->speed * cos(emitter->angle + speedAngle);
        speed.y = emitter->speed * sin(emitter->angle + speedAngle);
        groupSetSpeed(group, speed);
        
        groupSetType(group, GROUP_TYPE_HARMLESS);
        groupAdd(group, part);
        
        groupSetAdd(groups, group);
    }
    
    return groups;
}

bool emitterDraw(emitter_t* emitter){
    vect_t pos;
    double lineLen;
    double alphaOne, alphaTwo;
    
    if(!emitter) return false;
    
    // get pos
    pos = emitterGetPos(emitter);
    
    // alphas
    alphaOne = emitterGetAngle(emitter) - emitterGetAlpha(emitter);
    alphaTwo = emitterGetAngle(emitter) + emitterGetAlpha(emitter);
    
    // line length
    lineLen = MAX_EMITTER_LEN / MAX_VG * emitterGetSpeed(emitter);
    
    gfxColor(0, 0, 0);
    gfxLine(
        pos.x, pos.y,
        pos.x + lineLen * cos(alphaOne), pos.y + lineLen * sin(alphaOne)
    );
    gfxLine(
        pos.x, pos.y,
        pos.x + lineLen * cos(alphaTwo), pos.y + lineLen * sin(alphaTwo)
    );
    
    // calculate rectangle
    rect_t rect = {
        .left = pos.x - EMITTER_SIZE / 2,
        .right = pos.x + EMITTER_SIZE / 2,
        .bottom = pos.y - EMITTER_SIZE / 2,
        .top = pos.y + EMITTER_SIZE / 2
    };
    
    gfxRect(rect, true);
    
    return true;
}

void emitterFree(emitter_t* emitter){
    if(!emitter) return;
    
    free(emitter);
}