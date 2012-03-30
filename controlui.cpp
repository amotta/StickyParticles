//
//  controlui.cpp
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#include <GLUI/glui.h>

#include "controlui.h"

#define EXIT_ID 1

namespace {
	// listeners
	void (*onExit)();
	
	// GLUI
	GLUI* glui;
	GLUI_Button* exitButton;
}

void ctrlUIInit(){
	onExit = NULL;
	
	glui = GLUI_Master.create_glui("Control");
	exitButton = glui->add_button("EXIT", EXIT_ID, ctrlUIHandleEvent);
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
	}
}