//
//  gameui.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/30/12.
//

#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include "constants.h"
#include "game.h"
#include "gameui.h"

static void gameUIHandleRedraw();
static void gameUIHandleReshape(int x, int y);

static int sizeX, sizeY;
static int windowID;

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
	
	glutDisplayFunc(gameUIHandleRedraw);
	glutReshapeFunc(gameUIHandleReshape);
}

void gameUIHandleRedraw(){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Don't ask me why
    glLoadIdentity();
    
    // invoke drawing
    gameDraw();
	
	glutSwapBuffers();
}

void gameUIHandleIdle(){
	glutSetWindow(windowID);
    
    // TODO
    // gameUpdate();
    
    gameUIUpdate();
}

void gameUIUpdate(){
    glutPostRedisplay();
}

int gameUIGetWindow(){
	return windowID;
}

void gameUIHandleReshape(int x, int	y){
    double aspectRatio;
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
	
	glutPostRedisplay();
}