//
//  file.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#ifndef FILE_H
#define FILE_H

#include "game.h"

extern game_t* fileRead(const char* name);
extern void fileSetDebug(bool flag);

#endif
