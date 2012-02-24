//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdio.h>

#include "game.h"

static int gameFileReadScore(FILE* file){
    unsigned int score;
    while(fscanf(file, "%ud", &score) < 1){
        // gameFileSkip(file);
    }
    
    return 0;
}

static int gameFileParse(FILE* file){
    char buf[BUFSIZE];
    
    clearerr(file);
    while(fgets(buf, BUFSIZE, file)){
        // analyze content
    }
    
    if(ferror(file)){
        printf("ERROR: Error while reading file\n");
        return 1;
    }else{
        return 0;
    }
}

extern int gameFileRead(char* name){
    FILE* file = NULL;
    
    file = fopen(name, "r");
    if(!file){
        printf("ERROR: Could not open file\n");
        return 1;
    }
    
    gameFileParse(file);
    
    fclose(file);
    
    return 0;
}
