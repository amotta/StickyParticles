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
#include "rectangle.h"

enum GAME_ERROR_CODES {
    GAME_OK,
    GAME_ERROR_EOF,
    GAME_ERROR_FOPEN,
    GAME_ERROR_SCORE,
    GAME_ERROR_INTERVAL,
    GAME_ERROR_DISC,
    GAME_ERROR_DISC_INVALID,
    GAME_ERROR_EMITTER,
    GAME_ERROR_EMITTER_POS_INVALID,
    GAME_ERROR_EMITTERS,
    GAME_ERROR_GROUPTYPE,
    GAME_ERROR_GROUP,
    GAME_ERROR_GROUPS,
    GAME_ERROR_PART,
    GAME_ERROR_PARTS,
    GAME_ERROR_NEWLINE,
    GAME_ERROR_FCLOSE
};

char* GAME_ERROR_MESSAGES[] = {
    "No error",
    "Reached end of file",
    "Could not open file",
    "Could not read score",
    "Could not read interval",
    "Could not read disc",
    "Position of disc is invalid",
    "Could not read emitter",
    "Position of emitter is invalid",
    "Could not read number of emitters",
    "Could not read group type",
    "Could not read group",
    "Could not read number of groups",
    "Could not read particle",
    "Could not read number of particles",
    "No line break between two values",
    "Could not close file"
};  

static int gameFileSkip();
static int gameFileReadScore();
static int gameFileReadInterval();
static int gameFileReadDisc();
static int gameFileReadEmitter();
static int gameFileReadEmitters();
static int gameFileReadGroupType();
static int gameFileReadGroup();
static int gameFileReadGroups();
static int gameFileReadPart();

static int error;
static bool debug;
static FILE* file;
static char* fileName;
static unsigned int lineNumber;

// This function skips comments and whitespaces
// Muchas gracias to git for inspiration
static int gameFileSkip(){
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
                c = fgetc(file);
                
                // aight, it's Windows
                if(c != '\n'){
                    ungetc(c, file);
                }
                
            case '\n':
                comment = false;
                newLine = true;
                lineNumber++;
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

static int gameFileReadScore(){
    int error = GAME_OK;
    unsigned int score;
    
    error = gameFileSkip();
    
    // no line break needed before first value
    if(error != GAME_OK && error != GAME_ERROR_NEWLINE){
        return error;
    }
    
    if(fscanf(file, "%u", &score) < 1){
        return GAME_ERROR_SCORE;
    }
    
    if(debug){
        printf("Score: %u\n", score);
    }
    
    return GAME_OK;
}

static int gameFileReadInterval(){
    int error = GAME_OK;
    double interval;
    
    if((error = gameFileSkip()) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf", &interval) < 1){
        return GAME_ERROR_INTERVAL;
    }
    
    if(debug){
        printf("Interval: %f\n", interval);
    }
    
    return GAME_OK;
}

static int gameFileReadDisc(){
    int error = GAME_OK;
    
    circ_t disc;
    disc.r = R_DISC;
    
    if((error = gameFileSkip()) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf %lf", &disc.pos.x, &disc.pos.y) < 2){
        return GAME_ERROR_DISC;
    }
    
    if(debug){
        printf("Disc\n");
        printf(" X: %f, Y: %f\n", disc.pos.x, disc.pos.y);
    }
    
    // validation
    if(!isCircInGameCirc(disc)){
        return GAME_ERROR_DISC_INVALID;
    }
    
    return GAME_OK;
}

static int gameFileReadEmitter(){
    int error = GAME_OK;
    vect_t pos;
    double alpha, flow, speed;
    
    if((error = gameFileSkip()) != GAME_OK){
        return error;
    }
    
    if(
        fscanf(
            file,
            "%lf %lf %lf %lf %lf",
            &pos.x, &pos.y, &alpha, &flow, &speed
        ) < 5
    ){
        return GAME_ERROR_EMITTER;
    }
    
    if(debug){
        printf(
            " X: %f, Y: %f, Alpha: %f, Flow: %f, Speed: %f\n",
            pos.x, pos.y, alpha, flow, speed
        );
    }
    
    // validation
    if(isVectInGameCirc(pos) || !isVectInGameRect(pos)){
        return GAME_ERROR_EMITTER_POS_INVALID;
    }
    
    // TODO
    // Further validation
    
    return GAME_OK;
}

static int gameFileReadEmitters(){
    int error = GAME_OK;
    unsigned int numbEmitters;
    
    if((error = gameFileSkip()) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%u", &numbEmitters) < 1){
        return GAME_ERROR_EMITTERS;
    }
    
    if(debug){
        printf("Emitter count: %u\n", numbEmitters);
    }
    
    // read emitters
    unsigned int i;
    for(i = 0; i < numbEmitters; i++){
        if((error = gameFileReadEmitter()) != GAME_OK){
            return error;
        }
    }
    
    return GAME_OK;
}

static int gameFileReadGroupType(){
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

static int gameFileReadGroup(){
    int error = GAME_OK;
    double x, y, vx, vy, omega;
    unsigned int type, numbParts;
    
    if((error = gameFileSkip()) != GAME_OK){
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
    
    if(debug){
        printf(
            " X: %f, Y: %f, VX: %f, VY: %f,"
            " OMEGA: %f,"
            " TYPE: %s,"
            " PARTS COUNT: %u\n",
            x, y,vx, vy,
            omega,
            type == GROUP_TYPE_HARMLESS ? "HARMLESS" : "DANGEROUS",
            numbParts
        );
    }
    
    // read particles
    if(numbParts > 1){
        unsigned int i;
        for(i = 0; i < numbParts; i++){
            if((error = gameFileReadPart()) != GAME_OK){
                return error;
            }
        }
    }
    
    return GAME_OK;
}

static int gameFileReadGroups(){
    int error = GAME_OK;
    unsigned int numbGroups;
    
    if((error = gameFileSkip()) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%u", &numbGroups) < 1){
        return GAME_ERROR_GROUPS;
    }
    
    if(debug){
        printf("Group count: %u\n", numbGroups);
    }
    
    unsigned int i;
    for(i = 0; i < numbGroups; i++){
        if((error = gameFileReadGroup()) != GAME_OK){
            return error;
        }
    }
    
    return GAME_OK;
}

static int gameFileReadPart(){
    int error = GAME_OK;
    double x, y;
    
    if((error = gameFileSkip()) != GAME_OK){
        return error;
    }
    
    if(fscanf(file, "%lf %lf", &x, &y) < 2){
        return GAME_ERROR_PART;
    }
    
    if(debug){
        printf("  X: %lf, Y: %lf\n", x, y);
    }
    
    return GAME_OK;
}

extern int gameFileRead(char* name){
    error = GAME_OK;
    file = NULL;
    fileName = name;
    lineNumber = 1;
    
    if((file = fopen(fileName, "r")) == NULL){
        error = GAME_ERROR_FOPEN;
    }
    
    if(!error) error = gameFileReadScore();
    if(!error) error = gameFileReadInterval();
    if(!error) error = gameFileReadDisc();
    if(!error) error = gameFileReadEmitters();
    if(!error) error = gameFileReadGroups();
    
    if(file && fclose(file)){
        error = GAME_ERROR_FCLOSE;
    }
    
    return error;
}

extern void gamePrintError(){
    printf("\n");
    printf("ERROR in %s on line %u\n", fileName, lineNumber);
    printf(" %s\n", GAME_ERROR_MESSAGES[error]);
}

extern void gameSetDebug(bool flag){
    debug = flag;
}
