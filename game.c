//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>

#include "game.h"

// TODO: handle EOF
static int gameFileSkip(FILE* file){
    char c;
    bool comment = false;
    bool newLine = false;
    
    do{
        c = fgetc(file);
        
        if(c == ' '){
            newLine = false;
        }else if(c == '#'){
            newLine = false;
            comment = true;
        }else if(c == '\r' ||  c == '\n'){
            newLine = true;
            comment = false;
        }else{
            if(newLine){
                ungetc(c, file);
                return 0;
            }else if(!comment){
                printf("ERROR: Invalid character\n");
                return 1;
            }
            
            newLine = false;
        }
    }while(true);
}

static int gameFileReadScore(FILE* file){
    unsigned int score;
    while(fscanf(file, "%u", &score) < 1){
        if(gameFileSkip(file)){
            return 1;
        }
    }
    
    printf("Score read: %u\n", score);
    
    return 0;
}

extern int gameFileRead(char* name){
    FILE* file = NULL;
    
    file = fopen(name, "r");
    if(!file){
        printf("ERROR: Could not open file\n");
        return 1;
    }
    
    gameFileReadScore(file);
    
    fclose(file);
    
    return 0;
}
