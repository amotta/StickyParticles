//
//  game.h
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// TODO: move to group.h
#define GROUP_TYPE_HARMLESS 1
#define GROUP_TYPE_DANGEROUS 2

extern bool gameFileRead(char* name);
extern void gameSetDebug(bool flag);

#endif
