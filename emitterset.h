//
//  emitterset.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/11/12.
//

#ifndef EMITTERSET_H
#define EMITTERSET_H

#include <stdbool.h>

#include "emitter.h"
#include "groupset.h"

typedef struct EMITTER_SET emitterSet_t;

extern emitterSet_t* emitterSetNew(unsigned int numbEmitters);
extern unsigned int emitterSetGetNumb(emitterSet_t* set);
extern groupSet_t* emitterSetEmit(emitterSet_t* set, double deltaT);
extern bool emitterSetForEach(
    emitterSet_t* set, bool (*handle)(emitter_t* emitter)
);
extern void emitterSetFree(emitterSet_t* set);

#endif
