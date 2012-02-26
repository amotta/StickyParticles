//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "main.h"

static int gameFileSkip(FILE* file){
    char c;
    bool comment = false;
    
    do{
        c = fgetc(file);
        
        switch(c){
            case ' ':
            case '\t':
                break;
            
            case '#':
                comment = true;
                break;
            
            case '\r':
            case '\n':
                comment = false;
                break;
                
            case EOF:
                return GAME_ERROR_EOF;
                break;
                
            default:
                if(!comment){
                    ungetc(c, file);
                    return OK;
                }
        }
    }while(true);
}

static int gameFileReadScore(FILE* file){
    int error = OK;
    unsigned int score;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%u", &score) < 1){
        return GAME_ERROR_FORMAT;
    }
    
    // DEBUG
    printf("Score read: %u\n", score);
    
    return OK;
}

static int gameFileReadInterval(FILE* file){
    int error = OK;
    double interval;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%lf", &interval) < 1){
        return GAME_ERROR_FORMAT;
    }
    
    // DEBUG
    printf("Interval read: %f\n", interval);
    
    return OK;
}

static int gameFileReadDisc(FILE* file){
    int error = OK;
    double x, y;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%lf", &x) < 1){
        return GAME_ERROR_FORMAT;
    }
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%lf", &y) < 1){
        return GAME_ERROR_FORMAT;
    }
    
    printf("Disc X: %f, Disc Y: %f\n", x, y);
    
    return OK;
}

extern int gameFileRead(char* name){
    int error = OK;
    FILE* file = NULL;
    
    file = fopen(name, "r");
    if(!file){
        return GAME_ERROR_FOPEN;
    }
    
    error = error || gameFileReadScore(file);
    error = error || gameFileReadInterval(file);
    error = error || gameFileReadDisc(file);
    
    fclose(file);
    
    return OK;
}
