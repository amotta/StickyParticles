//
//  controlui.cpp
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#include <GLUI/glui.h>

#include "controlui.h"

enum UI_IDS {
    UI_ID_EXIT,
    UI_ID_FILE,
    UI_ID_LOAD,
    UI_ID_SAVE,
    UI_ID_INTERVAL,
    UI_ID_STEP,
    UI_ID_PLAY
};

namespace {
	// listeners
	void (*onExit)() = NULL;
    void (*onLoad)(const char* file) = NULL;
    
    // getters and setters
    double (*intGet)() = NULL;
    void (*intSet)(double value) = NULL;
    unsigned int (*scoreGet)() = NULL;
	
	// GLUI
	GLUI* glui = NULL;
    GLUI_EditText* fileText = NULL;
    GLUI_Spinner* deltaSpinner = NULL;
    GLUI_EditText* timeText = NULL;
    GLUI_EditText* scoreText = NULL;
    GLUI_EditText* statusText = NULL;
}

void ctrlUIInit(){
    GLUI_Panel* panel = NULL;
	
	glui = GLUI_Master.create_glui("Control");
    
    // load / save panel
    panel = glui->add_panel("Load/Save");
    
    fileText = glui->add_edittext_to_panel(
        panel,
        "File",
        GLUI_EDITTEXT_TEXT,
        NULL,
        UI_ID_FILE,
        ctrlUIHandleEvent
    );
    
    glui->add_button_to_panel(panel, "Load", UI_ID_LOAD, ctrlUIHandleEvent);
    glui->add_button_to_panel(panel, "Save", UI_ID_SAVE, ctrlUIHandleEvent);
    
    // simulation panel
    panel = glui->add_panel("Simulation");
    
    glui->add_spinner_to_panel(
        panel,
        "Interval",
        GLUI_SPINNER_FLOAT,
        NULL,
        UI_ID_INTERVAL,
        ctrlUIHandleEvent
    );
    
    glui->add_button_to_panel(panel, "Step", UI_ID_STEP, ctrlUIHandleEvent);
    glui->add_button_to_panel(panel, "Play", UI_ID_PLAY, ctrlUIHandleEvent);
    
    // information panel
    panel = glui->add_panel("Informations");
    
    timeText = glui->add_edittext_to_panel(
        panel, "Time", GLUI_EDITTEXT_FLOAT
    );
    
    scoreText = glui->add_edittext_to_panel(
        panel,
        "Score",
        GLUI_EDITTEXT_INT
    );
    
    statusText = glui->add_edittext_to_panel(
        panel,
        "Status",
        GLUI_EDITTEXT_TEXT
    );
    
    // exit button
	glui->add_button("Exit", UI_ID_EXIT, ctrlUIHandleEvent);
}

void ctrlUISetOnLoad(void (*load)(const char* file)){
    onLoad = load;
}

void ctrlUISetOnExit(void (*exit)()){
	onExit = exit;
}

void ctrlUISetIntervalGetter(double (*func)()){
    intGet = func;
}

void ctrlUISetIntervalSetter(void (*func)(double val)){
    intSet = func;
}

void ctrlUISetScoreGetter(unsigned int (*func)()){
    scoreGet = func;
}

void ctrlUISetGameWindow(int wind){
	glui->set_main_gfx_window(wind);
}
                             
void ctrlUIUpdate(){
    if(intGet) timeText->set_float_val(intGet());
    if(scoreGet) scoreText->set_int_val(scoreGet());
}

void ctrlUIHandleEvent(int id){
	switch(id){
		case UI_ID_EXIT:
			if(onExit) onExit();
			break;
            
        case UI_ID_LOAD:
            if(onLoad) onLoad(fileText->get_text());
            
            // update UI
            ctrlUIUpdate();
            
            break;
            
        case UI_ID_SAVE:
            break;
	}
}