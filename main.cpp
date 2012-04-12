//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#include "controlui.h"

extern "C" {
    #include "file.h"
    #include "gameui.h"
}

namespace {
    bool isOpt(char* arg);
    void handleOpt(char* arg);
    void usage();
    void handleExit();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
	
    // set up game UI
    gameUIInit();
    gameUISetOnRedraw(gameDraw);
    gameUISetOnIdle(NULL);

    // set up control UI
    ctrlUIInit();
    ctrlUISetOnExit(handleExit);
    ctrlUISetGameWindow(gameUIGetWindow());
	
    // set idle listener
    GLUI_Master.set_glutIdleFunc(gameUIHandleIdle);
    
    // handle arguments
    f(argc < 2){
        usage();
        return EXIT_SUCCESS;
    }
    
    for(i = 1; i < argc; i++){
        if(isOpt(argv[i])){
            handleOpt(argv[i]);
        }else{
            fileRead(argv[i]);
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
        fileSetDebug(true);
    }else if(!strcmp("-s", arg)){
        fileSetDebug(false);
    }
}

void usage(){
    printf(
           "Usage of Sticky Particles\n"
           " sticky.x file1 [file2 ... fileN]\n"
           " -v    Activate debugging\n"
           " -s    Deactivate debugging\n"
           );
}

void handleExit(){
    exit(EXIT_SUCCESS);
}