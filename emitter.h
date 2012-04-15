//
//  emitter.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#ifndef EMITTER_H
#define EMITTER_H

#include "vector.h"

typedef struct EMITTER emitter_t;

extern emitter_t* emitterNew();
extern void emitterSetPos(emitter_t* emitter, vect_t* pos);
extern void emitterGetAngle(emitter_t* emitter);
extern void emitterGetAlpha(emitter_t* emitter);
extern void emitterSetAlpha(emitter_t* emitter, double alpha);
extern void emitterSetFlow(emitter_t* emitter, double flow);
extern void emitterSetSpeed(emitter_t* emitter, double speed);
extern void emitterFree(emitter_t* emitter);

#endif
