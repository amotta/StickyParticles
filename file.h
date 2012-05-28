//
//  file.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#ifndef FILE_H
#define FILE_H

#include <stdbool.h>

#include "game.h"

// parses the file given by name. on success the newly constructed game is
// returned. in case of error NULL is returned.
extern game_t* fileRead(const char* name);

// write game to a file called name and returns true on success.
// else false is returned.
extern bool fileSave(game_t* game, const char* name);

// toggles debug messages for file module
extern void fileSetDebug(bool flag);

#endif
