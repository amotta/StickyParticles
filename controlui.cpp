//
//  controlui.cpp
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#include <GLUI/glui.h>

#include "controlui.h"

#define EXIT_ID 1
#define FILE_ID 2
#define LOAD_ID 3
#define SAVE_ID 4

namespace {
	// listeners
	void (*onExit)() = NULL;
    void (*onLoad)(const char* file) = NULL;
	
	// GLUI
	GLUI* glui = NULL;
    GLUI_EditText* fileText = NULL;
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
        FILE_ID,
        ctrlUIHandleEvent
    );
    
    glui->add_button_to_panel(panel, "Load", LOAD_ID, ctrlUIHandleEvent);
    glui->add_button_to_panel(panel, "Save", SAVE_ID, ctrlUIHandleEvent);
    
    // exit button
	glui->add_button("Exit", EXIT_ID, ctrlUIHandleEvent);
}

void ctrlUISetOnLoad(void (*load)(const char* file)){
    onLoad = load;
}

void ctrlUISetOnExit(void (*exit)()){
	onExit = exit;
}

void ctrlUISetGameWindow(int wind){
	glui->set_main_gfx_window(wind);
}

void ctrlUIHandleEvent(int id){
	switch(id){
		case EXIT_ID:
			if(onExit) onExit();
			break;
            
        case LOAD_ID:
            if(onLoad) onLoad(fileText->get_text());
            break;
            
        case SAVE_ID:
            break;
	}
}