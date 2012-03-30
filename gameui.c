//
//  gameui.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#include <GLUT/glut.h>

#include "gameui.h"

static int windowID;

void gameUIInit(){
	windowID = glutCreateWindow("Sticky Particles");
}

int gameUIGetWindow(){
	return windowID;
}