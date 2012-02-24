//
//  game.h
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdio.h>

#define BUFSIZE 255

static int gameFileReadScore(FILE* file);
static int gameFileParse(FILE* file);
extern int gameFileRead(char* name);
