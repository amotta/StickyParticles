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

// returns newly allocated and inited memory for a set of numbEmitters emitters
extern emitterSet_t* emitterSetNew(unsigned int numbEmitters);

// returns a deep copy of set
extern emitterSet_t* emitterSetCopy(emitterSet_t* set);

// returns the number of emitters in set
extern unsigned int emitterSetGetNumb(emitterSet_t* set);

// returns a groupSet containing all newly created groups
// by the emitters of set
extern groupSet_t* emitterSetEmit(emitterSet_t* set, double deltaT);

// applies function handle to all emitters of set
extern bool emitterSetForEach(
    emitterSet_t* set, bool (*handle)(emitter_t* emitter)
);

// frees the given set and all associated emitters
extern void emitterSetFree(emitterSet_t* set);

#endif
