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
    printf("Score: %u\n", score);
    
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
    printf("Interval: %f\n", interval);
    
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
    
    // DEBUG
    printf("Disc\n");
    printf(" X: %f, Y: %f\n", x, y);
    
    return OK;
}

static int gameFileReadEmitter(FILE* file){
    int error = OK;
    double x, y, alpha, flow, speed;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%lf %lf %lf %lf %lf", &x, &y, &alpha, &flow, &speed) < 5){
        return GAME_ERROR_FORMAT;
    }
    
    printf(
        " X: %f, Y: %f, Alpha: %f, Flow: %f, Speed: %f\n",
        x, y, alpha, flow, speed
    );
    
    return OK;
}

static int gameFileReadEmitters(FILE* file){
    int error = OK;
    unsigned int numbEmitters;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%u", &numbEmitters) < 1){
        return GAME_ERROR_FORMAT;
    }
    
    // DEBUG
    printf("Emitter count: %u\n", numbEmitters);
    
    // read emitters
    unsigned int i;
    for(i = 0; i < numbEmitters; i++){
        if(error = gameFileReadEmitter(file)){
            return error;
        }
    }
    
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
    error = error || gameFileReadEmitters(file);
    
    fclose(file);
    
    return OK;
}
