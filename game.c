//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdlib.h>

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
        gameInit(game);
    }else{
        printf("Could not allocate memory for new game\n");
        exit(EXIT_FAILURE);
    }
    
    return game;
}

void gameInit(game_t* game){
    if(!game) return;
    
    game->score = 0;
    game->interval = 0;
    
    discFree(game->disc);
    game->disc = NULL;
    
    emitterSetFree(game->emitters);
    game->emitters = NULL;
    
    // TODO
    // groupSetFree(game->groups);
    game->groups = NULL;
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

void gameSetEmitters(game_t* game, emitterSet_t* emitter){
    if(!game || !emitters) return;
    
    game->emitters = emitters;
}

void gameSetGroups(game_t* game, groupSet_t* groups){
    if(!game || !groups) return;
    
    game->groups = groups;
}

void gameFree(game_t* game){
    if(!game) return;
    
    gameInit(game);
    free(game);
}

void gameDraw(){
    gfxClear();
    gfxGameCirc();
}

