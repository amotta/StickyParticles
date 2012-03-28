//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdlib.h>
#include <OpenGL/glu.h>

#include "controlui.h"

void handleExit(int id){
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    
    ControlUI controlUI;
	controlUI.onExit(handleExit);
	controlUI.init();
    
    glutMainLoop();
	
	return EXIT_SUCCESS;
}