//
//  controlui.cpp
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#include <stdlib.h>

#ifdef __APPLE__
    #include <GLUI/glui.h>
#else
    #include <GL/glui.h>
#endif

#include "controlui.h"
#include "main.h"

extern "C" {
    #include "game.h"
}

#define DELTA_SPINNER_MIN 0.05
#define DELTA_SPINNER_MAX 0.2
#define DELTA_SPINNER_STEPS 5

enum UI_IDS {
    UI_ID_EXIT,
    UI_ID_LOAD,
    UI_ID_RESET,
    UI_ID_SAVE,
    UI_ID_INTERVAL,
    UI_ID_STEP,
    UI_ID_PLAY
};

const char* STATE_MESSAGES[] = {
    (const char*) "Ready",
    (const char*) "Reset",
    (const char*) "File OK",
    (const char*) "File NOK",
    (const char*) "Playing",
    (const char*) "Stopped",
    (const char*) "Game Over"
};

namespace {
    game_t* currentGame = NULL;
    const char* currentFile = NULL;
    
    // callbacks
    void (*onLoad)(const char* file) = NULL;
    void (*onReset)() = NULL;
    void (*onSave)() = NULL;
    void (*onStep)() = NULL;
    void (*onPlay)() = NULL;
    
    // GLUI
	GLUI* glui = NULL;
    GLUI_EditText* loadedText = NULL;
    GLUI_EditText* fileText = NULL;
    GLUI_Button* resetButton = NULL;
    GLUI_Button* saveButton = NULL;
    
    GLUI_Panel* simPanel = NULL;
    GLUI_Spinner* deltaSpinner = NULL;
    GLUI_EditText* timeText = NULL;
    GLUI_EditText* scoreText = NULL;
    GLUI_EditText* statusText = NULL;
}

static void ctrlUIHandleEvent(int id);

void ctrlUIInit(){
    GLUI_Panel* panel = NULL;
	
    // new window
	glui = GLUI_Master.create_glui("Control");
    
    // load / save panel
    panel = glui->add_panel("Load/Save");
    
    loadedText = glui->add_edittext_to_panel(
        panel, "Loaded", GLUI_EDITTEXT_TEXT
    );
    
    fileText = glui->add_edittext_to_panel(
        panel, "File", GLUI_EDITTEXT_TEXT
    );
    
    if(fileText){
        fileText->set_text("test1.txt");
    }
    
    // create load button
    glui->add_button_to_panel(panel, "Load", UI_ID_LOAD, ctrlUIHandleEvent);
    
    resetButton = glui->add_button_to_panel(
        panel, "Reset", UI_ID_RESET, ctrlUIHandleEvent
    );
    
    // create save button
    saveButton = glui->add_button_to_panel(
        panel, "Save", UI_ID_SAVE, ctrlUIHandleEvent
    );
    
    // simulation panel
    simPanel = glui->add_panel("Simulation");
    
    deltaSpinner = glui->add_spinner_to_panel(
        simPanel,
        "Interval",
        GLUI_SPINNER_FLOAT,
        NULL,
        UI_ID_INTERVAL,
        ctrlUIHandleEvent
    );
    
    // config delta spinner
    deltaSpinner->set_float_limits(DELTA_SPINNER_MIN, DELTA_SPINNER_MAX);
    deltaSpinner->set_speed(
        (DELTA_SPINNER_MAX - DELTA_SPINNER_MIN) / DELTA_SPINNER_STEPS
    );

    glui->add_button_to_panel(simPanel, "Step", UI_ID_STEP, ctrlUIHandleEvent);
    glui->add_button_to_panel(simPanel, "Play", UI_ID_PLAY, ctrlUIHandleEvent);
    
    // information panel
    panel = glui->add_panel("Informations");
    
    timeText = glui->add_edittext_to_panel(
        panel, "Time", GLUI_EDITTEXT_FLOAT
    );
    
    scoreText = glui->add_edittext_to_panel(
        panel, "Score", GLUI_EDITTEXT_INT
    );
    
    statusText = glui->add_edittext_to_panel(
        panel, "Status", GLUI_EDITTEXT_TEXT
    );
    
    // exit button
	glui->add_button("Exit", UI_ID_EXIT, ctrlUIHandleEvent);
    
    // update
    ctrlUIUpdate();
}

void ctrlUISetGameWindow(int wind){
	glui->set_main_gfx_window(wind);
}

void ctrlUISetOnLoad(void (*func)(const char* file)){
    onLoad = func;
}

void ctrlUISetOnReset(void (*func)()){
    onReset = func;
}

void ctrlUISetOnSave(void (*func)()){
    onSave = func;
}

void ctrlUISetOnStep(void (*func)()){
    onStep = func;
}

void ctrlUISetOnPlay(void (*func)()){
    onPlay = func;
}

void ctrlUISetState(int state){
    switch(state){
        case STATE_READY:
            resetButton->disable();
            saveButton->disable();
            simPanel->disable();
            break;
        case STATE_RESET:
            simPanel->enable();
            break;
        case STATE_FILE_OK:
            resetButton->enable();
            saveButton->enable();
            simPanel->enable();
            break;
        case STATE_FILE_NOK:
            // nothing
            break;
        case STATE_PLAYING:
            simPanel->disable();
            break;
        case STATE_STOPPED:
            simPanel->enable();
        case STATE_GAME_OVER:
            // nothing
            break;
    }
    
    // change state text
    statusText->set_text(STATE_MESSAGES[state]);
}

void ctrlUISetFile(const char* file){
    currentFile = file;
}

void ctrlUISetGame(game_t* game){
    currentGame = game;
}
                             
void ctrlUIUpdate(){
    if(currentFile){
        loadedText->set_text(currentFile);
    }else{
        loadedText->set_text("No file");
    }
    
    // NOTE
    // works with currentGame = NULL too
    deltaSpinner->set_float_val(gameGetInterval(currentGame));
    timeText->set_float_val(gameGetTime(currentGame));
    scoreText->set_int_val(gameGetScore(currentGame));
}

void ctrlUIHandleEvent(int id){
	switch(id){
		case UI_ID_EXIT:
            gameFree(currentGame);
            
            // terminate process
            exit(EXIT_SUCCESS);
			break;
            
        case UI_ID_LOAD:
            if(onLoad){
                onLoad(fileText->get_text());
            }
            
            break;
        
        case UI_ID_RESET:
            if(onReset){
                onReset();
            }
            
            break;
            
        case UI_ID_SAVE:
            if(onSave){
                onSave();
            }
            
            break;
            
        case UI_ID_INTERVAL:
            if(currentGame){
                gameSetInterval(
                    currentGame,
                    deltaSpinner->get_float_val()
                );
            }
            break;
            
        case UI_ID_STEP:
            if(onStep){
                onStep();
            }
            break;
            
        case UI_ID_PLAY:
            if(onPlay){
                onPlay();
            }
            
            break;
	}
}