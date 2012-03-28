//
//  controlui.cpp
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#include <GLUI/glui.h>

#include "controlui.h"

ControlUI::ControlUI(){
	exitHandle = NULL;
}

void ControlUI::init(){
    glui = GLUI_Master.create_glui("Control");
	exitButton = glui->add_button("EXIT", CONTROLUI_EXIT_ID, exitHandle);
}

void ControlUI::onExit(void (*callback)(int)){
	exitHandle = callback;
}