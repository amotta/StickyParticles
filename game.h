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

// TODO: move to group.h
#define GROUP_TYPE_NONE 0
#define GROUP_TYPE_HARMLESS 1
#define GROUP_TYPE_DANGEROUS 2

extern int gameFileRead(char* name);

#endif
