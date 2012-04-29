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

static void gameSetCurrentFile(const char* file);

static bool debug;
static char* currentFile;
static game_t* currentGame;

struct GAME {
    unsigned int score;
    double interval;
    circ_t disc;
    emitterSet_t* emitters;
    groupSet_t* groups;
};

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

void gameSetScore(game_t* game, unsigned int score){
    if(!game) return;
    
    game->score = score;
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

void gameFree(game_t* game){
    if(!game) return;
    
    emitterSetFree(game->emitters);
    game->emitters = NULL;
    
    groupSetFree(game->groups);
    game->groups = NULL;
    
    free(game);
}

void gameCurrentFree(){
    if(currentGame){
        gameFree(currentGame);
    }
}

bool gameLoad(const char* file){
    game_t* newGame = NULL;
    
    // TODO
    // Create deep copy
    newGame = fileRead(file);
    
    if(newGame){
        gameCurrentFree();
        
        // set new game
        currentGame = newGame;
        
        // TODO
        // deep copy
        
        // update currentFile
        gameSetCurrentFile(file);
        
        return true;
    }else{
        return false;
    }
}

unsigned int gameGetCurrentScore(){
    if(!currentGame) return 0;
    
    return currentGame->score;
}

double gameGetCurrentInterval(){
    if(!currentGame) return 0;
    
    return currentGame->interval;
}

const char* gameGetCurrentFile(){
    if(currentFile){
        return currentFile;
    }else{
        return "No file";
    }
}

void gameDraw(){
    gfxColor(1, 1, 1);
    gfxClear();
    
    // game rect
    gfxColor(0, 0, 0);
    gfxRect(getGameRect(), false);
    
    // game circ
    gfxColor(0, 0, 0);
    gfxCirc(getGameCirc(), false);
    
    // if game loaded
    if(currentGame){
        // game disc
        gfxColor(0, 0, 1);
        gfxCirc(currentGame->disc, true);
        
        // groups
        groupSetForEach(currentGame->groups, groupDraw);
        
        // emitters
        emitterSetForEach(currentGame->emitters, emitterDraw);
    }
}

void gameSetDebug(bool flag){
    debug = flag;
    
    fileSetDebug(flag);
}

void gameSetCurrentFile(const char* file){
    // free old string
    if(currentFile){
        free(currentFile);
        currentFile = NULL;
    }
    
    // calculate bufLen
    int bufLen = strlen(file) + 1;
    
    // allocate new buffer
    if((currentFile = malloc(bufLen))){
        memcpy(currentFile, file, bufLen);
    }else{
       printf("Could not allocate memory for file name\n");
       exit(EXIT_FAILURE);
    }
}
