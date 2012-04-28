//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdlib.h>

#ifdef __APPLE__
    #include <GLUI/glui.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glui.h>
    #include <GL/glut.h>
#endif

#include "controlui.h"

extern "C" {
    #include "game.h"
    #include "gameui.h"
}

static bool isOpt(char* arg);
static void handleOpt(char* arg);
static void handleKeyboard(unsigned char key, int x, int y);
static void handleSpecial(int key, int x, int y);
static void handleMouse(int button, int state, int x, int y);
static void usage();

int main(int argc, char** argv){
    char* file = NULL;
    
    glutInit(&argc, argv);
	
    // set up game UI
    gameUIInit();

    // set up control UI
    ctrlUIInit();
    ctrlUISetGameWindow(gameUIGetWindow());
	
    // set idle listener
    GLUI_Master.set_glutIdleFunc(NULL);
    GLUI_Master.set_glutKeyboardFunc(handleKeyboard);
    GLUI_Master.set_glutSpecialFunc(handleSpecial);
    GLUI_Master.set_glutMouseFunc(handleMouse);
    
    // show usage indications
    usage();
    
    for(int i = 1; i < argc; i++){
        if(isOpt(argv[i])){
            handleOpt(argv[i]);
        }else{
            file = argv[i];
        }
    }
    
    // load the last file specified
    if(file){
        gameLoad(file);
    }
    
    gameUIUpdate();
    ctrlUIUpdate();
    glutMainLoop();
	
    return EXIT_SUCCESS;
}

bool isOpt(char* arg){
    if(arg[0] == '-'){
        return true;
    }else{
        return false;
    }
}

void handleOpt(char* arg){
    if(!strcmp("-v", arg)){
        gameSetDebug(true);
    }else if(!strcmp("-s", arg)){
        gameSetDebug(false);
    }
}

void handleKeyboard(unsigned char key, int x, int y){
    printf("Key #%d pressed\n", key);
}

void handleSpecial(int key, int x, int y){
    printf("Special key #%d pressed \n", key);
}

void handleMouse(int button, int state, int x, int y){
    printf(
        "Mouse key #%d changed to state #%d at X: %d Y: %d\n",
        button, state, x, y
    );
}

void usage(){
    printf(
        "Usage of Sticky Particles\n"
        " sticky.x file1 [file2 ... fileN]\n"
        " -v    Activate debugging\n"
        " -s    Deactivate debugging\n"
        "\n"
    );
}