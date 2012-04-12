//
//  emitter.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#ifndef EMITTER_H
#define EMITTER_H

typedef struct EMITTER emitter_t;

extern void emitterInit(emitter_t* emitter);
extern void emitterSetAlpha(emitter_t* emitter, double alpha);
extern void emitterSetFlow(emitter_t* emitter, double flow);
extern void emitterSetSpeed(emitter_t* emitter, double speed);
extern void emitterFree(emitter_t* emitter);

#endif
