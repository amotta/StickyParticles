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
#include "emitterset.h"
#include "file.h"
#include "game.h"
#include "graphics.h"
#include "groupset.h"
#include "rectangle.h"

struct GAME {
    unsigned int score;
    double interval;
    circ_t disc;
    emitterSet_t* emitters;
    groupSet_t* groups;
};

static void gameDrawBackground();

game_t* gameNew(){
    game_t* game = NULL;
    
    if((game = malloc(sizeof(game_t)))){
        game->score = 0;
        game->interval = 0;
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
    
    // TODO
    // 1 Emit particles
    newGroups = emitterSetEmit(game->emitters, game->interval);
    
    if(newGroups){
        groupSetMerge(game->groups, newGroups);
        newGroups = NULL;
    }
    
    // 2 Move particles
    groupSetMove(game->groups, game->interval);
    
    // 3 Detect collisions
    groupSetForEach(game->groups, groupCheckBorder);
    groupSetCollide(game->groups);
    
    // 4 Move disc
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