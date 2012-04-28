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

#define DELTA_SPINNER_MIN 0.05
#define DELTA_SPINNER_MAX 0.2
#define DELTA_SPINNER_STEPS 5

extern "C" {
    #include "game.h"
    #include "gameui.h"
}

enum UI_IDS {
    UI_ID_EXIT,
    UI_ID_LOAD,
    UI_ID_SAVE,
    UI_ID_INTERVAL,
    UI_ID_STEP,
    UI_ID_PLAY
};

enum STATES {
    STATE_READY,
    STATE_FILE_OK,
    STATE_FILE_NOK,
    STATE_GAME_OVER
};

namespace {
    int state = STATE_READY;
    char* STATE_MESSAGES[] = {
        (char*) "Ready",
        (char*) "File OK",
        (char*) "File NOK",
        (char*) "Game Over"
    };
    
    // GLUI
	GLUI* glui = NULL;
    GLUI_EditText* loadedText = NULL;
    GLUI_EditText* fileText = NULL;
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
    
    glui->add_button_to_panel(panel, "Load", UI_ID_LOAD, ctrlUIHandleEvent);
    glui->add_button_to_panel(panel, "Save", UI_ID_SAVE, ctrlUIHandleEvent);
    
    // simulation panel
    panel = glui->add_panel("Simulation");
    
    deltaSpinner = glui->add_spinner_to_panel(
        panel,
        "Interval",
        GLUI_SPINNER_FLOAT,
        NULL,
        UI_ID_INTERVAL,
        ctrlUIHandleEvent
    );
        
    deltaSpinner->set_float_limits(DELTA_SPINNER_MIN, DELTA_SPINNER_MAX);
    deltaSpinner->set_speed(
        (DELTA_SPINNER_MAX - DELTA_SPINNER_MIN) / DELTA_SPINNER_STEPS
    );
    
    glui->add_button_to_panel(panel, "Step", UI_ID_STEP, ctrlUIHandleEvent);
    glui->add_button_to_panel(panel, "Play", UI_ID_PLAY, ctrlUIHandleEvent);
    
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
    
    statusText->set_text(STATE_MESSAGES[state]);
    
    // exit button
	glui->add_button("Exit", UI_ID_EXIT, ctrlUIHandleEvent);
    
    // update
    ctrlUIUpdate();
}

void ctrlUISetGameWindow(int wind){
	glui->set_main_gfx_window(wind);
}
                             
void ctrlUIUpdate(){
    loadedText->set_text(gameGetCurrentFile());
    deltaSpinner->set_float_val(gameGetCurrentInterval());
    scoreText->set_int_val(gameGetCurrentScore());
    statusText->set_text(STATE_MESSAGES[state]);
}

void ctrlUIHandleEvent(int id){
	switch(id){
		case UI_ID_EXIT:
            // TODO
            // free game
            
            exit(EXIT_SUCCESS);
			break;
            
        case UI_ID_LOAD:
            // load game file
            if(gameLoad(fileText->get_text())){
                state = STATE_FILE_OK;
            }else{
                state = STATE_FILE_NOK;
            }
            
            // update UI
            ctrlUIUpdate();
            gameUIUpdate();
            break;
            
        case UI_ID_SAVE:
            // TODO
            // gameSaveCurrent(fileText->get_text());
            printf("Save button pressed\n");
            break;
            
        case UI_ID_INTERVAL:
            // TODO
            // gameSetCurrentInterval(deltaSpinner->get_float_val());
            printf("Interval changed\n");
            break;
            
        case UI_ID_STEP:
            // TODO
            printf("Step button pressed\n");
            break;
            
        case UI_ID_PLAY:
            // TODO
            printf("Play button pressed\n");
            break;
	}
}