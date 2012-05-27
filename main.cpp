//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "controlui.h"

extern "C" {
    #include "file.h"
    #include "game.h"
    #include "gameui.h"
    #include "main.h"
}

namespace {
    int state = STATE_READY;
    
    char* currentFile = NULL;
    game_t* originalGame = NULL;
    game_t* currentGame = NULL;
}

// arg handling
static bool isOpt(char* arg);
static void handleOpt(char* arg);
static void handleKeyboard(unsigned char key, int x, int y);
static void handleTimer(int val);

// UI handling
static void playGame();
static void stepGame();
static void updateGame();
static void stopGame();
static void loadFile(const char* file);
static void resetGame();
static void saveFile();

// misc
static void copyGame();
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
    ctrlUISetOnReset(resetGame);
    ctrlUISetOnSave(saveFile);
    ctrlUISetOnPlay(playGame);
    
    // register keyboard callback
    glutKeyboardFunc(handleKeyboard);
    
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
    switch(key){
        case 'q':
            exit(EXIT_SUCCESS);
            break;
            
        case 'j':
            playGame();
            break;
            
        case 'e':
            stopGame();
            break;
            
        case 's':
            stepGame();
            break;
            
        case 'r':
            resetGame();
            break;
            
        case 'w':
            saveFile();
            break;
            
        case 't':
            printf("LOAD TEMP\n");
            break;
    }
}

void handleTimer(int val){
    if(!currentGame) return;
    if(state != STATE_PLAYING) return;
    
    // prepare timer
    setTimer();
    
    // simulate delta T
    updateGame();
}

void playGame(){
    if(!currentGame) return;
    if(
        state != STATE_RESET
        && state != STATE_FILE_OK
        && state != STATE_STOPPED
    ) return; 
    
    // change state
    setState(STATE_PLAYING);
    
    // prepare timer
    setTimer();
}

void stepGame(){
    if(!currentGame) return;
    if(
       state != STATE_RESET
       && state != STATE_FILE_OK
       && state != STATE_STOPPED
    ) return;
    
    updateGame();
}

void updateGame(){
    bool update;
    
    if(!currentGame) return;
    
    // let's move 
    update = gameUpdate(currentGame);
    
    // are you boss enough?
    if(!update){
        // celebrate end of game
        setState(STATE_GAME_OVER);
    }
    
    // update UI
    ctrlUIUpdate();
    gameUIUpdate();
}

void stopGame(){
    if(state != STATE_PLAYING) return;
    
    // stop game
    setState(STATE_STOPPED);
}

void loadFile(const char* file){
    game_t* newGame = NULL;
    
    if(!file) return;
    
    // try to load game
    newGame = fileRead(file);
    
    // change state
    if(newGame){
        // set new file
        setFile(file);
        
        // ... and change state
        setState(STATE_FILE_OK);
        
        // free old game
        if(originalGame){
            gameFree(originalGame);
            originalGame = NULL;
        }
        
        // set new game
        originalGame = newGame;
        
        // copy game
        copyGame();
    }else{
        setState(STATE_FILE_NOK);
    }
}

void resetGame(){
    if(!originalGame) return;
    
    // change state
    setState(STATE_RESET);
    
    copyGame();
}

void copyGame(){
    if(!originalGame) return;
    
    // free old game
    if(currentGame){
        free(currentGame);
        currentGame = NULL;
    }
    
    // new copy
    currentGame = gameCopy(originalGame);
    
    // tell about new game
    ctrlUISetGame(currentGame);
    gameUISetGame(currentGame);
    
    // update UI
    ctrlUIUpdate();
    gameUIUpdate();
}

void saveFile(){
    if(!currentGame) return;
    
    // try to save game
    if(fileSave(currentGame, "temp.txt")){
        setFile("temp.txt");
    }
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
    ctrlUISetState(newState);
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
            currentFile = NULL;
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