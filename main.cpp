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
    #include "file.h"
    #include "game.h"
    #include "gameui.h"
}

enum STATE {
    STATE_READY,
    STATE_FILE_OK,
    STATE_FILE_NOK,
    STATE_GAME_OVER
};

namespace {
    int state = STATE_READY;
    const char* STATE_MESSAGES[] = {
        (const char*) "Ready",
        (const char*) "File OK",
        (const char*) "File NOK",
        (const char*) "Game Over"
    };
    
    char* currentFile = NULL;
    game_t* currentGame = NULL;
}

// arg handling
static bool isOpt(char* arg);
static void handleOpt(char* arg);

// event handling
static void handleKeyboard(unsigned char key, int x, int y);
static void handleSpecial(int key, int x, int y);
static void handleTimer(int val);

// UI handling
static void playGame();
static void loadFile(const char* file);

// misc
static void setTimer();
static void setState(int state);
static void setFile(const char* file);
static void usage();

int main(int argc, char** argv){
    char* file = NULL;
    
    glutInit(&argc, argv);
	
    // set up game UI
    gameUIInit();

    // set up control UI
    ctrlUIInit();
    ctrlUISetGameWindow(gameUIGetWindow());
    ctrlUISetOnLoad(loadFile);
    ctrlUISetOnPlay(playGame);
	
    // set idle listener
    GLUI_Master.set_glutKeyboardFunc(handleKeyboard);
    GLUI_Master.set_glutSpecialFunc(handleSpecial);
    
    // set status
    setState(STATE_READY);
    
    // show usage indications
    usage();
    
    for(int i = 1; i < argc; i++){
        if(isOpt(argv[i])){
            handleOpt(argv[i]);
        }else{
            file = argv[i];
        }
    }
    
    // load the last file
    if(file){
        loadFile(file);
    }
    
    gameUIUpdate();
    ctrlUIUpdate();
    
    // start event handling
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

void handleKeyboard(unsigned char key, int x, int y){
    printf("Key #%d pressed\n", key);
}

void handleSpecial(int key, int x, int y){
    printf("Special key #%d pressed \n", key);
}

void handleTimer(int val){
    setTimer();
    gameUpdate(currentGame);
    gameUIUpdate();
}

void playGame(){
    setTimer();
}

void loadFile(const char* file){
    game_t* newGame = NULL;
    
    if(!file) return;
    
    // try to load game
    newGame = fileRead(file);
    
    // change state
    if(newGame){
        setFile(file);
        setState(STATE_FILE_OK);
        
        // free old game
        if(currentGame){
            gameFree(currentGame);
        }
        
        // set new game
        currentGame = newGame;
    }else{
        setState(STATE_FILE_NOK);
    }
    
    ctrlUISetGame(currentGame);
    gameUISetGame(currentGame);
    
    // update UI
    ctrlUIUpdate();
    gameUIUpdate();
}

void setTimer(){
    glutTimerFunc(
        1000 * gameGetInterval(currentGame),
        handleTimer,
        0
    );
}

void setState(int newState){
    state = newState;
    
    // update state in control UI
    ctrlUISetState(STATE_MESSAGES[newState]);
}

void setFile(const char* file){
    char* newFile = NULL;
    
    if(!file) return;
    
    // calculate bufLen
    int bufLen = strlen(file) + 1;
    
    // allocate new buffer
    if((newFile = (char*) malloc(bufLen))){
        memcpy(newFile, file, bufLen);
        
        // free old buffer
        if(currentFile){
            free(currentFile);
        }
        
        // update current file
        currentFile = newFile;
    }else{
        printf("Could not allocate memory for file name\n");
        exit(EXIT_FAILURE);
    }
    
    // update file in control UI
    ctrlUISetFile(currentFile);
}

void usage(){
    printf(
        "Usage of Sticky Particles\n"
        " sticky.x [file1]\n"
        " -v    Activate debugging\n"
        " -s    Deactivate debugging\n"
        "\n"
    );
}