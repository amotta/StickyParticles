//
//  emitter.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#ifndef EMITTER_H
#define EMITTER_H

#include <stdbool.h>

#include "group.h"
#include "vector.h"

typedef struct EMITTER emitter_t;

// allocates and inits memory for new emitter
extern emitter_t* emitterNew();

// return a deep copy of emitter
extern emitter_t* emitterCopy(emitter_t* emitter);

// returns the position vector of emitter
extern vect_t emitterGetPos(emitter_t* emitter);

// changes the position vector of emitter to pos
extern void emitterSetPos(emitter_t* emitter, vect_t pos);

// returns the angle between emitter and the game rectangle's center
extern double emitterGetAngle(emitter_t* emitter);

// returns the alpha angle of emitter
extern double emitterGetAlpha(emitter_t* emitter);

// changes to alpha angle of emitter to alpha
extern void emitterSetAlpha(emitter_t* emitter, double alpha);

// returns the flow of emitter
extern double emitterGetFlow(emitter_t* emitter);

// changes the flow of emitter to flow
extern void emitterSetFlow(emitter_t* emitter, double flow);

// returns the speed of emitter
extern double emitterGetSpeed(emitter_t* emitter);

// changes the speed of emitter to speed
extern void emitterSetSpeed(emitter_t* emitter, double speed);

// returns a newly created group when emitter emits in deltaT
// else NULL is returned
extern group_t* emitterEmit(emitter_t* emitter, double deltaT);

// draws emitter
extern bool emitterDraw(emitter_t* emitter);

// frees the emitter allocated with emitterNew
extern void emitterFree(emitter_t* emitter);

#endif
