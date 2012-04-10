//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "circle.h"
#include "constants.h"
#include "game.h"
#include "geometry.h"
#include "graphics.h"
#include "rectangle.h"
#include "vector.h"

static void gameSetError(int errorCode);
static void gamePrintStatus();

extern void gameDraw(){
    gfxClear();
    gfxGameCirc();
}

