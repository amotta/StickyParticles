//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdlib.h>
#include <GLUT/glut.h>

#include "controlui.h"

extern "C" {
    #include "game.h"
    #include "gameui.h"
}
	
void handleExit(){
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
	
    gameUIInit();
    gameUISetOnRedraw(gameDraw);
    gameUISetOnIdle(NULL);

    ctrlUIInit();
    ctrlUISetOnExit(handleExit);
    ctrlUISetGameWindow(gameUIGetWindow());
	
    // set idle listener
    GLUI_Master.set_glutIdleFunc(gameUIHandleIdle);
    
    glutMainLoop();
	
    return EXIT_SUCCESS;
}