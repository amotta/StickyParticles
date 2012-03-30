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
	#include "gameui.h"
}
	
void handleExit(){
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
	
	gameUIInit();
	
	ctrlUIInit();
	ctrlUISetOnExit(handleExit);
	ctrlUISetGameWindow(gameUIGetWindow());
    
    glutMainLoop();
	
	return EXIT_SUCCESS;
}