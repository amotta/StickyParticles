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

enum GAME_ERROR_CODES {
    GAME_OK,
    GAME_ERROR_EOF,
    GAME_ERROR_FOPEN,
    GAME_ERROR_SCORE,
    GAME_ERROR_INTERVAL,
    GAME_ERROR_DISC,
    GAME_ERROR_EMITTER,
    GAME_ERROR_EMITTERS,
    GAME_ERROR_GROUPTYPE,
    GAME_ERROR_GROUP,
    GAME_ERROR_GROUPS,
    GAME_ERROR_PART,
    GAME_ERROR_PARTS,
    GAME_ERROR_NEWLINE,
    GAME_ERROR_FCLOSE
};

static int gameFileSkip(FILE* file);
static int gameFileReadScore(FILE* file);
static int gameFileReadInterval(FILE* file);
static int gameFileReadDisc(FILE* file);
static int gameFileReadEmitter(FILE* file);
static int gameFileReadEmitters(FILE* file);
static int gameFileReadGroupType(FILE* file);
static int gameFileReadGroup(FILE* file);
static int gameFileReadGroups(FILE* file);
static int gameFileReadPart(FILE* file);

static int gameFileSkip(FILE* file){
    char c;
    bool comment = false;
    bool newLine = false;
    
    do{
        c = fgetc(file);
        
        switch(c){
            case ' ':
            case '\t':
                continue;
            
            case '#':
                comment = true;
                continue;
            
            case '\r':
            case '\n':
                comment = false;
                newLine = true;
                continue;
                
            case EOF:
                return GAME_ERROR_EOF;
                
            default:
                if(!comment){
                    ungetc(c, file);
                    
                    if(newLine){
                        return GAME_OK;
                    }else{
                        return GAME_ERROR_NEWLINE;
                    }
                }
        }
    }while(true);
}

static int gameFileReadScore(FILE* file){
    int error = GAME_OK;
    unsigned int score;
    
    error = gameFileSkip(file);
    
    // no line break needed before first value
    if(error != GAME_OK && error != GAME_ERROR_NEWLINE){
        return error;
    }
    
    if(fscanf(file, "%u", &score) < 1){
        return GAME_ERROR_SCORE;
    }
    
    // DEBUG
    printf("Score: %u\n", score);
    
    return GAME_OK;
}

static int gameFileReadInterval(FILE* file){
    int error = GAME_OK;
    double interval;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf", &interval) < 1){
        return GAME_ERROR_INTERVAL;
    }
    
    // DEBUG
    printf("Interval: %f\n", interval);
    
    return GAME_OK;
}

static int gameFileReadDisc(FILE* file){
    int error = GAME_OK;
    double x, y;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf %lf", &x, &y) < 2){
        return GAME_ERROR_DISC;
    }
    
    // DEBUG
    printf("Disc\n");
    printf(" X: %f, Y: %f\n", x, y);
    
    return GAME_OK;
}

static int gameFileReadEmitter(FILE* file){
    int error = GAME_OK;
    double x, y, alpha, flow, speed;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf %lf %lf %lf %lf", &x, &y, &alpha, &flow, &speed) < 5){
        return GAME_ERROR_EMITTER;
    }
    
    // DEBUG
    printf(
        " X: %f, Y: %f, Alpha: %f, Flow: %f, Speed: %f\n",
        x, y, alpha, flow, speed
    );
    
    return GAME_OK;
}

static int gameFileReadEmitters(FILE* file){
    int error = GAME_OK;
    unsigned int numbEmitters;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%u", &numbEmitters) < 1){
        return GAME_ERROR_EMITTERS;
    }
    
    // DEBUG
    printf("Emitter count: %u\n", numbEmitters);
    
    // read emitters
    unsigned int i;
    for(i = 0; i < numbEmitters; i++){
        if((error = gameFileReadEmitter(file)) != GAME_OK){
            return error;
        }
    }
    
    return GAME_OK;
}

static int gameFileReadGroupType(FILE* file){
    char buf[11];
    if(fscanf(file, "%10s", buf) < 1){
        return GROUP_TYPE_NONE;
    }
    
    // check for valid values
    if(!strcmp(buf, "INOFFENSIF")){
        return GROUP_TYPE_HARMLESS;
    }else if(!strcmp(buf, "DANGEREUX")){
        return GROUP_TYPE_DANGEROUS;
    }else{
        return GROUP_TYPE_NONE;
    }
}

static int gameFileReadGroup(FILE* file){
    int error = GAME_OK;
    double x, y, vx, vy, omega;
    unsigned int type, numbParts;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf %lf %lf %lf %lf", &x, &y, &vx, &vy, &omega) < 5){
        return GAME_ERROR_GROUP;
    }
    
    if((type = gameFileReadGroupType(file)) == GROUP_TYPE_NONE){
        return GAME_ERROR_GROUPTYPE;
    }
    
    if(fscanf(file, "%u", &numbParts) < 1){
        return GAME_ERROR_PARTS;
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
    
    // read particles
    if(numbParts > 1){
        unsigned int i;
        for(i = 0; i < numbParts; i++){
            if((error = gameFileReadPart(file)) != GAME_OK){
                return error;
            }
        }
    }
    
    return GAME_OK;
}

static int gameFileReadGroups(FILE* file){
    int error = GAME_OK;
    unsigned int numbGroups;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%u", &numbGroups) < 1){
        return GAME_ERROR_GROUPS;
    }
    
    // DEUBG
    printf("Group count: %u\n", numbGroups);
    
    unsigned int i;
    for(i = 0; i < numbGroups; i++){
        if((error = gameFileReadGroup(file)) != GAME_OK){
            return error;
        }
    }
    
    return GAME_OK;
}

static int gameFileReadPart(FILE* file){
    int error = GAME_OK;
    double x, y;
    
    if((error = gameFileSkip(file)) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf %lf", &x, &y) < 2){
        return GAME_ERROR_PART;
    }
    
    // DEBUG
    printf("  X: %lf, Y: %lf\n", x, y);
    
    return GAME_OK;
}

extern int gameFileRead(char* name){
    int error = GAME_OK;
    FILE* file = NULL;
    
    if((file = fopen(name, "r")) == NULL){
        return GAME_ERROR_FOPEN;
    }
    
    error = error || gameFileReadScore(file);
    error = error || gameFileReadInterval(file);
    error = error || gameFileReadDisc(file);
    error = error || gameFileReadEmitters(file);
    error = error || gameFileReadGroups(file);
    
    fclose(file);
    
    return error;
}
