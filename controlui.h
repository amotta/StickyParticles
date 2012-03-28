//
//  controlui.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#ifndef CONTROLUI_H
#define CONTROLUI_H

#include <GLUI/glui.h>

#define CONTROLUI_EXIT_ID 1
	
class ControlUI {
    private:
        GLUI* glui;
		GLUI_Button* exitButton;
		void (*exitHandle)(int);
    
    public:
		ControlUI();
		void init();
		void onExit(void (*handle)(int));
};

#endif
