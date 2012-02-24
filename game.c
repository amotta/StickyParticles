//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>

#include "game.h"

static int gameFileSkip(FILE* file){
    char c;
    int ret = -1;
    bool comment = false;
    bool newLine = false;
    
    do{
        c = fgetc(file);
        
        if(c = ' '){
            newLine = false;
        }else if(c = '#'){
            newLine = false;
            comment = true;
        }else if(c = '\r' ||  c = '\n'){
            newLine = true;
            comment = false;
        }else{
            if(newLine){
                ungetc(c, file);
                ret = 0;
            }else if(!comment){
                ret = 1;
            }
            
            newLine = false;
        }
    }while(ret < 0);
    
    return ret;
}

static int gameFileReadScore(FILE* file){
    unsigned int score;
    while(fscanf(file, "%ud", &score) < 1){
        if(gameFileSkip(file)){
            return 1;
        }
    }
    
    return 0;
}

static int gameFileParse(FILE* file){
    gameFileReadScore(file);
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
