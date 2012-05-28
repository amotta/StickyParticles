//
//  gameui.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#ifndef GAME_UI
#define GAME_UI

#include "game.h"

// init GLUT window
extern void gameUIInit();

// force window to redraw its content
extern void gameUIUpdate();

// returns handle of GLUT window
extern int gameUIGetWindow();

// set current game to game
extern void gameUISetGame(game_t* game);

#endif
