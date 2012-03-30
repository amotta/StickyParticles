//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdlib.h>
#include <OpenGL/glu.h>

#include "controlui.h"

void handleExit(){
	exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
	
	ctrlUIInit();
	ctrlUIOnExit(handleExit);
    
    glutMainLoop();
	
	return EXIT_SUCCESS;
}