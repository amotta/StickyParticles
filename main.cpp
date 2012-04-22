//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdlib.h>
#include <GLUI/glui.h>
#include <GLUT/glut.h>

#include "controlui.h"

extern "C" {
    #include "game.h"
    #include "gameui.h"
}

bool isOpt(char* arg);
void handleOpt(char* arg);
void usage();

int main(int argc, char** argv){
    glutInit(&argc, argv);
	
    // set up game UI
    gameUIInit();

    // set up control UI
    ctrlUIInit();
    ctrlUISetGameWindow(gameUIGetWindow());
	
    // set idle listener
    GLUI_Master.set_glutIdleFunc(NULL);
    
    // show usage indications
    usage();
    
    for(int i = 1; i < argc; i++){
        if(isOpt(argv[i])){
            handleOpt(argv[i]);
        }else{
            gameLoad(argv[i]);
        }
    }
    
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

void usage(){
    printf(
        "Usage of Sticky Particles\n"
        " sticky.x file1 [file2 ... fileN]\n"
        " -v    Activate debugging\n"
        " -s    Deactivate debugging\n"
        "\n"
    );
}