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
    double xMin, xMax;
    double yMin, yMax;
    double pxPerUnit;
    double diff;
    
	sizeX = x;
	sizeY = y;
	aspectRatio = (double) x / y;
    
    // calculate extremes
    if(aspectRatio > RECT_X / RECT_Y){
        // too wide
        yMin = 0;
        yMax = RECT_Y;
        
        pxPerUnit = sizeY / RECT_Y;
        diff = (sizeX / pxPerUnit - RECT_X) / 2;
        
        xMin = 0 - diff;
        xMax = RECT_X + diff;
    }else{
        // too high
        xMin = 0;
        xMax = RECT_X;
        
        pxPerUnit = sizeX / RECT_X;
        diff = (sizeY / pxPerUnit - RECT_Y) / 2;
        
        yMin = 0 - diff;
        yMax = RECT_Y + diff;
    }
	
    // use full window
	glViewport(0, 0, sizeX, sizeY);
	
    // set coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xMin, xMax, yMin, yMax, -1, +1);
	
    // change to modelview matrix
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	glutPostRedisplay();
}

int gameUIGetWindow(){
	return windowID;
}