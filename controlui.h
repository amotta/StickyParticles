//
//  controlui.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#ifndef CONTROLUI_H
#define CONTROLUI_H

extern "C" {
    #include "game.h"
}

extern void ctrlUIInit();
extern void ctrlUISetGameWindow(int gameWindow);
extern void ctrlUISetOnLoad(void (*func)(const char* file));
extern void ctrlUISetState(const char* state);
extern void ctrlUISetFile(const char* file);
extern void ctrlUISetGame(game_t* game);
extern void ctrlUIUpdate();

#endif
