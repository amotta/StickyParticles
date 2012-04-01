//
//  gameui.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "constants.h"
#include "gameui.h"

static void gameUIHandleRedraw();
static void gameUIHandleReshape(int x, int y);

static int sizeX, sizeY;
static double aspectRatio;
static int windowID;
static void (*onRedraw)();
static void (*onIdle)();

void gameUIInit(){
	sizeX = 600;
	sizeY = 400;
	
	// create window
	glutInitWindowSize(sizeX, sizeY);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	windowID = glutCreateWindow("Sticky Particles");
	
	// init projection matrix
	gameUIHandleRedraw(sizeX, sizeY);
	
	// set clear color
	glClearColor(1, 1, 1, 0);
	
	glutDisplayFunc(gameUIHandleRedraw);
	glutReshapeFunc(gameUIHandleReshape);
}

void gameUISetOnRedraw(void (*redraw)()){
	onRedraw = redraw;
}

void gameUIHandleRedraw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	if(onRedraw) onRedraw();
	
	glutSwapBuffers();
}

void gameUISetOnIdle(void (*idle)()){
	onIdle = idle;
}

void gameUIHandleIdle(){
	glutSetWindow(windowID);
	
	if(onIdle) onIdle();
	
	glutPostRedisplay();
}

void gameUIHandleReshape(int x, int	y){
	sizeX = x;
	sizeY = y;
	aspectRatio = (double) x / y;
	
	glViewport(0, 0, sizeX, sizeY);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, RECT_X, 0, RECT_Y, -1, +1);
	
	glMatrixMode(GL_MODELVIEW);
	
	glutPostRedisplay();
}

int gameUIGetWindow(){
	return windowID;
}