//
//  gameui.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#ifndef GAME_UI
#define GAME_UI

extern void gameUIInit();
extern void gameUIHandleIdle();
extern void gameUISetOnRedraw(void (*redraw)());
extern void gameUISetOnIdle(void (*idle)());
extern int gameUIGetWindow();

#endif
