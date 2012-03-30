//
//  controlui.h
//  StickyParticles
//
//  Created by Alessandro Motta on 3/28/12.
//

#ifndef CONTROLUI_H
#define CONTROLUI_H

#include <GLUI/glui.h>

extern void ctrlUIInit();
extern void ctrlUIOnExit(void (*exit)());
extern void ctrlUIShow();
extern void ctrlUIHandleEvent(int id);

#endif
