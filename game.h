//
//  game.h
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#define GAME_ERROR_EOF 1
#define GAME_ERROR_FORMAT 2
#define GAME_ERROR_FOPEN 3

static int gameFileSkip(FILE* file);
static int gameFileReadScore(FILE* file);
static int gameFileReadInterval(FILE* file);
static int gameFileReadDisc(FILE* file);
extern int gameFileRead(char* name);

#endif
