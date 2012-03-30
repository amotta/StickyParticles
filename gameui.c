//
//  gameui.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#include <GLUT/glut.h>

#include "gameui.h"

static void gameUIHandleRedraw();
static void gameUIHandleReshape(int x, int y);

static int sizeX, sizeY;
static double aspectRatio;
static int windowID;
static void (*onRedraw)();

void gameUIInit(){
	windowID = glutCreateWindow("Sticky Particles");
	
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	glutDisplayFunc(gameUIHandleRedraw);
	glutReshapeFunc(gameUIHandleReshape);
}

void gameUISetOnRedraw(void (*redraw)()){
	onRedraw = redraw;
}

void gameUIHandleRedraw(){
	// TODO
	// glOrtho
	// glClearColorBit
	// glLoadIdenity
	// blabla
	
	if(onRedraw) onRedraw();
	
	glutSwapBuffers();
}

void gameUIHandleReshape(int x, int y){
	sizeX = x;
	sizeY = y;
	aspectRatio = (double) x / y;
	
	glutPostRedisplay();
}

int gameUIGetWindow(){
	return windowID;
}