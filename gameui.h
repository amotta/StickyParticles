//
//  gameui.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#ifndef GAME_UI
#define GAME_UI

extern void gameUIInit();
extern void gameUIUpdate();
extern int gameUIGetWindow();
extern void gameSetOnDraw(void (*func)());

#endif
