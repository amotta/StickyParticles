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
#define GAME_ERROR_NO_SEPA 4

extern int gameFileRead(char* name);

#endif
