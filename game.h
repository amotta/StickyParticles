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
extern unsigned int gameGetCurrentScore();
extern void gameSetScore(game_t* game, unsigned int score);
extern double gameGetCurrentInterval();
extern void gameSetInterval(game_t* game, double timeDiff);
extern void gameSetDisc(game_t* game, circ_t disc);
extern void gameSetEmitters(game_t* game, emitterSet_t* emitters);
extern void gameSetGroups(game_t* game, groupSet_t* groups);
extern void gameFree(game_t* game);

extern bool gameLoad(const char* file);
extern void gameDraw();
extern void gameSetDebug(bool flag);

#endif
