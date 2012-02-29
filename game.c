//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "main.h"

static int gameFileSkip(FILE* file);
static int gameFileReadScore(FILE* file);
static int gameFileReadInterval(FILE* file);
static int gameFileReadDisc(FILE* file);
static int gameFileReadEmitter(FILE* file);
static int gameFileReadEmitters(FILE* file);
static int gameFileReadGroupType(FILE* file);
static int gameFileReadGroup(FILE* file);
static int gameFileReadGroups(FILE* file);

static int gameFileSkip(FILE* file){
    char c;
    bool comment = false;
    bool separation = false;
    
    do{
        c = fgetc(file);
        
        switch(c){
            case ' ':
            case '\t':
                separation = true;
                break;
            
            case '#':
                comment = true;
                break;
            
            case '\r':
            case '\n':
                comment = false;
                separation = true;
                break;
                
            case EOF:
                return GAME_ERROR_EOF;
                break;
                
            default:
                if(!comment){
                    ungetc(c, file);
                    
                    if(separation){
                        return OK;
                    }else{
                        return GAME_ERROR_NO_SEPA;
                    }
                }
        }
    }while(true);
}

static int gameFileReadScore(FILE* file){
    int error = OK;
    unsigned int score;
    
    // no separator needed at start of file
    if(
       error = gameFileSkip(file)
       && error != GAME_ERROR_NO_SEPA
    ){
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

static int gameFileReadGroupType(FILE* file){
    int error = OK;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    char buf[11];
    if(fscanf(file, "%10s", buf) < 1){
        return GROUP_TYPE_NONE;
    }
    
    if(!strcmp(buf, "INOFFENSIF")){
        return GROUP_TYPE_HARMLESS;
    }else if(!strcmp(buf, "DANGEREUX")){
        return GROUP_TYPE_DANGEROUS;
    }else{
        return GROUP_TYPE_NONE;
    }
}

static int gameFileReadGroup(FILE* file){
    int error = OK;
    double x, y, vx, vy, omega;
    int type;
    unsigned int numbParts;
    
    if(error = gameFileSkip(file)){
        printf("ERROR 208\n");
        return error;
    }
    
    if(fscanf(file, "%lf %lf %lf %lf %lf", &x, &y, &vx, &vy, &omega) < 5){
        printf("ERROR 213\n");
        return GAME_ERROR_FORMAT;
    }
    
    if((type = gameFileReadGroupType(file)) == GROUP_TYPE_NONE){
        // TODO proper error message
        printf("ERROR 219\n");
        return GAME_ERROR_FORMAT;
    }
    
    if(fscanf(file, "%u", &numbParts) < 1){
        printf("ERROR 224\n");
        return GAME_ERROR_FORMAT;
    }
    
    // DEBUG
    printf(
        " X: %f, Y: %f, VX: %f, VY: %f, OMEGA: %f, TYPE: %s, PARTS COUNT: %u\n",
        x, y,
        vx, vy,
        omega,
        type == GROUP_TYPE_HARMLESS ? "HARMLESS" : "DANGEROUS",
        numbParts
    );
    
    return OK;
}

static int gameFileReadGroups(FILE* file){
    int error = OK;
    unsigned int numbGroups;
    
    if(error = gameFileSkip(file)){
        return error;
    }
    
    if(fscanf(file, "%u", &numbGroups) < 1){
        return GAME_ERROR_FORMAT;
    }
    
    // DEUBG
    printf("Group count: %u\n", numbGroups);
    
    unsigned int i;
    for(i = 0; i < numbGroups; i++){
        if(error = gameFileReadGroup(file)){
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
    error = error || gameFileReadGroups(file);
    
    fclose(file);
    
    return OK;
}
