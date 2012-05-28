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

// inits the GLUI window
extern void ctrlUIInit();

// register main graphics window
extern void ctrlUISetGameWindow(int gameWindow);

// register load handler
extern void ctrlUISetOnLoad(void (*func)(const char* file));

// register reset handler
extern void ctrlUISetOnReset(void (*func)());

// register save handler
extern void ctrlUISetOnSave(void (*func)());

// register step handler
extern void ctrlUISetOnStep(void (*func)());

// register play handler
extern void ctrlUISetOnPlay(void (*func)());

// changes the current state
extern void ctrlUISetState(int state);

// changes the current file
extern void ctrlUISetFile(const char* file);

// sets the current game
extern void ctrlUISetGame(game_t* game);

// forces GLUI to display the most recent values
extern void ctrlUIUpdate();

#endif
