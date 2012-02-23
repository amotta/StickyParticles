//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdio.h>

#include "game.h"

extern int gameFileRead(char* name){
    FILE* file = NULL;
    char buf[BUFSIZE];
    
    file = fopen(name, "r");
    if(!file){
        printf("ERROR: Could not open file\n");
        return 1;
    }
    
    fclose(file);
    
    return 0;
}
