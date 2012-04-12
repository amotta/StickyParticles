//
//  particleset.h
//  StickyParticles
//
//  Created by Alessandro Motta on 4/12/12.
//

#ifndef PARTICLE_SET_H
#define PARTICLE_SET_H

typedef struct PART_SET partSet_t;

extern partSet_t* partSetNew();
extern void partSetAdd(partSet_t* set, part_t* part);
extern void partSetFree(partSet_t* set);

#endif
