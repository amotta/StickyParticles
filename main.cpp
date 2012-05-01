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
static void handleMouse(int button, int state, int x, int y);

// UI handling
static void loadFile(const char* file);
static void drawGame();

// misc
static void setState(int state);
static void setFile(const char* file);
static void usage();

int main(int argc, char** argv){
    char* file = NULL;
    
    glutInit(&argc, argv);
	
    // set up game UI
    gameUIInit();
    gameUISetOnDraw(drawGame);

    // set up control UI
    ctrlUIInit();
    ctrlUISetGameWindow(gameUIGetWindow());
    ctrlUISetOnLoad(loadFile);
	
    // set idle listener
    GLUI_Master.set_glutIdleFunc(NULL);
    GLUI_Master.set_glutKeyboardFunc(handleKeyboard);
    GLUI_Master.set_glutSpecialFunc(handleSpecial);
    GLUI_Master.set_glutMouseFunc(handleMouse);
    
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
    
    // update UI
    ctrlUIUpdate();
    gameUIUpdate();
}

void drawGame(){
    gameDraw(currentGame);
}

void setState(int newState){
    state = newState;
    ctrlUISetState(STATE_MESSAGES[newState]);
}

void setFile(const char* file){
    if(!file) return;
    
    // free old string
    if(currentFile){
        free(currentFile);
        currentFile = NULL;
    }
    
    // calculate bufLen
    int bufLen = strlen(file) + 1;
    
    // allocate new buffer
    if((currentFile = malloc(bufLen))){
        memcpy(currentFile, file, bufLen);
    }else{
        printf("Could not allocate memory for file name\n");
        exit(EXIT_FAILURE);
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