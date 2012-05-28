//
//  game.h
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "circle.h"
#include "emitterset.h"
#include "groupset.h"

typedef struct GAME game_t;

// allocate and init memory for new game
extern game_t* gameNew();

// create deep copy of game
extern game_t* gameCopy(game_t* game);

// return the score of game
extern unsigned int gameGetScore(const game_t* game);

// set the score of game to score
extern void gameSetScore(game_t* game, unsigned int score);

// reset the time of game to zero
extern void gameResetTime(game_t* game);

// returns the time of game
extern double gameGetTime(game_t* game);

// returns the interval of game
extern double gameGetInterval(const game_t* game);

// changes the interval of game to timeDiff
extern void gameSetInterval(game_t* game, double timeDiff);

// changes the game circle's target in game to target 
extern void gameSetTarget(game_t* game, vect_t target);

// returns the game disc of game
extern circ_t gameGetDisc(game_t* game);

// changes the game disc of game to disc
extern void gameSetDisc(game_t* game, circ_t disc);

// returns the emitterSet of game
extern emitterSet_t* gameGetEmitters(game_t* game);

// changes the emitterSet of game to emitters
extern void gameSetEmitters(game_t* game, emitterSet_t* emitters);

// returns the groupSet of game
extern groupSet_t* gameGetGroups(game_t* game);

// changes the groupSet of game to groups
extern void gameSetGroups(game_t* game, groupSet_t* groups);

// simulates a time interval
extern bool gameUpdate(game_t* game);

// draws game
extern void gameDraw(const game_t* game);

// frees game and all associate groups and emitters
extern void gameFree(game_t* game);

#endif
