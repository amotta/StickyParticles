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

extern game_t* gameNew();
extern unsigned int gameGetScore(const game_t* game);
extern void gameSetScore(game_t* game, unsigned int score);
extern double gameGetInterval(const game_t* game);
extern void gameSetInterval(game_t* game, double timeDiff);
extern void gameSetTarget(game_t* game, vect_t target);
extern void gameSetDisc(game_t* game, circ_t disc);
extern void gameSetEmitters(game_t* game, emitterSet_t* emitters);
extern void gameSetGroups(game_t* game, groupSet_t* groups);
extern bool gameUpdate(game_t* game);
extern void gameDraw(const game_t* game);
extern void gameFree(game_t* game);

#endif
