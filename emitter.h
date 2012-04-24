//
//  emitter.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#ifndef EMITTER_H
#define EMITTER_H

#include <stdbool.h>

#include "vector.h"

typedef struct EMITTER emitter_t;

extern emitter_t* emitterNew();
extern vect_t emitterGetPos(emitter_t* emitter);
extern void emitterSetPos(emitter_t* emitter, vect_t pos);
extern double emitterGetAngle(emitter_t* emitter);
extern double emitterGetAlpha(emitter_t* emitter);
extern void emitterSetAlpha(emitter_t* emitter, double alpha);
extern void emitterSetFlow(emitter_t* emitter, double flow);
extern double emitterGetSpeed(emitter_t* emitter);
extern void emitterSetSpeed(emitter_t* emitter, double speed);
extern bool emitterDraw(emitter_t* emitter);
extern void emitterFree(emitter_t* emitter);

#endif
