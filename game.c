//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circle.h"
#include "constants.h"
#include "emitterset.h"
#include "file.h"
#include "game.h"
#include "graphics.h"
#include "groupset.h"
#include "rectangle.h"
#include "vector.h"

struct GAME {
    unsigned int score;
    double interval;
    vect_t target;
    circ_t disc;
    emitterSet_t* emitters;
    groupSet_t* groups;
};

static void gameDrawBackground();
static void gameUpdateDisc(game_t* game);

game_t* gameNew(){
    game_t* game = NULL;
    
    if((game = malloc(sizeof(game_t)))){
        game->score = 0;
        game->interval = 0;
        game->target = vectGetNull();
        game->disc = circGetNull();
        game->emitters = NULL;
        game->groups = NULL;
    }else{
        printf("Could not allocate memory for new game\n");
        exit(EXIT_FAILURE);
    }
    
    return game;
}

unsigned int gameGetScore(const game_t* game){
    if(!game) return 0;
    
    return game->score;
}

void gameSetScore(game_t* game, unsigned int score){
    if(!game) return;
    
    game->score = score;
}

double gameGetInterval(const game_t* game){
    if(!game) return 0;
    
    return game->interval;
}

void gameSetInterval(game_t* game, double interval){
    if(!game) return;
    
    game->interval = interval;
}

void gameSetTarget(game_t* game, vect_t target){
    if(!game) return;
    
    game->target = target;
}

void gameSetDisc(game_t* game, circ_t disc){
    if(!game) return;
    
    game->disc = disc;
}

void gameSetEmitters(game_t* game, emitterSet_t* emitters){
    if(!game || !emitters) return;
    
    game->emitters = emitters;
}

void gameSetGroups(game_t* game, groupSet_t* groups){
    if(!game || !groups) return;
    
    game->groups = groups;
}

void gameUpdate(game_t* game){
    groupSet_t* newGroups = NULL;
    
    if(!game) return;
    
    // 1 Emit particles
    newGroups = emitterSetEmit(game->emitters, game->interval);
    
    if(newGroups){
        groupSetMerge(game->groups, newGroups);
        groupSetFree(newGroups);
        newGroups = NULL;
    }
    
    // 2 Move particles
    groupSetMove(game->groups, game->interval);
    
    // 3 Detect collisions
    groupSetForEach(game->groups, groupCheckBorder);
    groupSetCollide(game->groups);
    
    // 4 Move disc
    gameUpdateDisc(game);
}

void gameUpdateDisc(game_t* game){
    double alpha;
    double maxDiff;
    vect_t target;
    circ_t targetCirc;
    vect_t diff;
    vect_t dir;
    
    if(!game) return;
    
    // init
    maxDiff = game->interval * MAX_VDISC;
    targetCirc.pos = game->target;
    targetCirc.r = R_DISC;
    
    if(isCircInCirc(targetCirc, getGameCirc())){
        target = game->target;
    }else{
        diff = vectSub(getGameCenter(), game->target);
        alpha = atan2(diff.y, diff.x);
        
        dir.x = (RECT_Y / 2 - R_DISC) * cos(alpha);
        dir.y = (RECT_Y / 2 - R_DISC) * sin(alpha);
        
        target = vectAdd(getGameCenter(), dir);
    }
    
    // calculate difference
    diff = vectSub(game->disc.pos, target);
    
    if(vectLen(diff) < maxDiff){
        game->disc.pos = target;
    }else{
        alpha = atan2(diff.y, diff.x);
    
        dir.x = maxDiff * cos(alpha);
        dir.y = maxDiff * sin(alpha);
    
        game->disc.pos = vectAdd(game->disc.pos, dir);
    }
}

void gameDrawBackground(){
    gfxColor(1, 1, 1);
    gfxClear();
    
    // game rect
    gfxColor(0, 0, 0);
    gfxRect(getGameRect(), false);
    
    // game circ
    gfxColor(0, 0, 0);
    gfxCirc(getGameCirc(), false);
}

void gameDraw(const game_t* game){
    gameDrawBackground();
    
    if(!game) return;
    
    // game disc
    gfxColor(0, 0, 1);
    gfxCirc(game->disc, true);
    
    // groups
    groupSetForEach(game->groups, groupDraw);
    
    // emitters
    emitterSetForEach(game->emitters, emitterDraw);
}

void gameFree(game_t* game){
    if(!game) return;
    
    emitterSetFree(game->emitters);
    game->emitters = NULL;
    
    groupSetFree(game->groups);
    game->groups = NULL;
    
    free(game);
}