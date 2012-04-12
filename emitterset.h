//
//  emitterset.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef EMITTERSET_H
#define EMITTERSET_H

typedef struct EMITTER_SET emitterSet_t;

extern emitter_t* emitterSetNew(unsigned int numbEmitters);
extern void emitterSetFree(emitterSet_t* set);

#endif
