//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "circle.h"
#include "emitterset.h"
#include "file.h"
#include "game.h"
#include "graphics.h"
#include "group.h"
#include "groupset.h"
#include "particle.h"

static void gameDrawGroups();
static bool gameDrawGroup(group_t* group);
static bool gameDrawPart(part_t* part);

static bool debug;
static game_t* currentGame;

struct GAME {
    unsigned int score;
    double interval;
    circ_t* disc;
    emitterSet_t* emitters;
    groupSet_t* groups;
};

game_t* gameNew(){
    game_t* game = NULL;
    
    if(game = malloc(sizeof(game_t))){
        game->score = 0;
        game->interval = 0;
        game->disc = NULL;
        game->emitters = NULL;
        game->groups = NULL;
    }else{
        printf("Could not allocate memory for new game\n");
        exit(EXIT_FAILURE);
    }
    
    return game;
}

void gameSetScore(game_t* game, unsigned int score){
    if(!game) return;
    
    game->score = score;
}

void gameSetInterval(game_t* game, double interval){
    if(!game) return;
    
    game->interval = interval;
}

void gameSetDisc(game_t* game, circ_t* disc){
    if(!game || !disc) return;
    
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

void gameFree(game_t* game){
    if(!game) return;
    
    circFree(game->disc);
    emitterSetFree(game->emitters);
    groupSetFree(game->groups);
    free(game);
}

void gameLoad(char* file){
    game_t* game = NULL;
    
    if((game = fileRead(file))){
        // TODO
        // Create complete copy
        currentGame = game;
    }
}

void gameDraw(){
    gfxColor(1, 1, 1);
    gfxClear();
    
    gfxColor(1, 0.8, 0.8);
    gfxCirc(getGameCirc(), true);
    
    // for each group in game
    groupSetForEach(currentGame->groups, gameDrawGroup);
}

bool gameDrawGroup(group_t* group){
    gfxColor(0.5, 0.5, 1);
    
    // for each particle of group
    groupForEach(group, gameDrawPart);
    
    return true;
}

bool gameDrawPart(part_t* part){
    static circ_t* circ;
    
    if(!part) return false;
    
    if(!circ){
        circ = circNew();
        circSetRadius(circ, R_PART);
    }
    
    // set up circle
    circSetPos(circ, partGetPos(part));
    
    // draw circle
    gfxCirc(circ, false);
    
    // unset pos
    circSetPos(circ, NULL);
    
    return true;
}

void gameSetDebug(bool flag){
    debug = flag;
    
    fileSetDebug(flag);
}
