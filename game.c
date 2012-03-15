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

#define LINE_BUF_LEN 81

static bool gameFileSkip();
static char* gameFileReadLine();
static bool gameFileReadScore();
static bool gameFileReadInterval();
static bool gameFileReadDisc();
static bool gameFileReadEmitter();
static bool gameFileReadEmitters();
static bool gameFileReadGroup();
static bool gameFileReadGroups();
static bool gameFileReadPart();

enum GAME_ERROR_CODES {
    GAME_OK,
    GAME_ERROR_EOF,
    GAME_ERROR_FOPEN,
    GAME_ERROR_FGETS,
    GAME_ERROR_LINE_TOO_LONG,
    GAME_ERROR_SCORE,
    GAME_ERROR_INTERVAL,
    GAME_ERROR_DISC,
    GAME_ERROR_DISC_POS,
    GAME_ERROR_EMITTER,
    GAME_ERROR_EMITTER_ALPHA,
    GAME_ERROR_EMITTER_POS,
    GAME_ERROR_EMITTER_SPEED,
    GAME_ERROR_EMITTERS,
    GAME_ERROR_GROUPTYPE,
    GAME_ERROR_GROUP,
    GAME_ERROR_GROUP_SPEED,
    GAME_ERROR_GROUPS,
    GAME_ERROR_PART,
    GAME_ERROR_PART_POS,
    GAME_ERROR_FCLOSE
};

static char* GAME_ERROR_MESSAGES[] = {
    "No error",
    "Reached end of file",
    "Could not open file",
    "Could not read line from file",
    "Line is too long",
    "Could not read score",
    "Could not read interval",
    "Could not read disc",
    "Position of disc is invalid",
    "Could not read emitter",
    "Emitter angle is invalid",
    "Position of emitter is invalid",
    "Speed of emitter is invalid",
    "Could not read number of emitters",
    "Could not read group type",
    "Could not read group",
    "Speed of group is invalid",
    "Could not read number of groups",
    "Could not read particle",
    "Position of particle is invalid",
    "Could not close file"
};

static int error;
static bool debug;
static FILE* file;
static char* fileName;
static unsigned int lineNumber;

// This function skips comments and whitespaces
// Muchas gracias to git for inspiration
static bool gameFileSkip(){
    char c;
    bool comment = false;
    
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
                lineNumber++;
                continue;
                
            case EOF:
                error = GAME_ERROR_EOF;
                return false;
                
            default:
                if(!comment){
                    ungetc(c, file);
                    return true;
                }
        }
    }while(true);
}

static char* gameFileReadLine(){
    static char line[LINE_BUF_LEN];
    
    if(!gameFileSkip()){
        return NULL;
    }
    
    if(fgets(line, LINE_BUF_LEN, file) == NULL){
        error = GAME_ERROR_FGETS;
        return NULL;
    }
    
    // level up
    lineNumber++;
    
    // check if we had enough space for the entire line
    if(line[strlen(line) - 1] != '\n'){
        error = GAME_ERROR_LINE_TOO_LONG;
        return NULL;
    }
    
    // seach for comment sign
    char* comment = strstr(line, "#");
    if(comment){
        *comment = '\0';
    }
    
    return line;
}

static bool gameFileReadScore(){
    char* line;
    unsigned int score;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(sscanf(line, "%u", &score) < 1){
        error = GAME_ERROR_SCORE;
        return false;
    }
    
    if(debug){
        printf("Score: %u\n", score);
    }
    
    return true;
}

static bool gameFileReadInterval(){
    char* line;
    double interval;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(sscanf(line, "%lf", &interval) < 1){
        error = GAME_ERROR_INTERVAL;
        return false;
    }
    
    if(debug){
        printf("Interval: %f\n", interval);
    }
    
    return true;
}

static bool gameFileReadDisc(){
    char* line;
    circ_t disc = {
        .r = R_DISC
    };
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(sscanf(line, "%lf %lf", &disc.pos.x, &disc.pos.y) < 2){
        error = GAME_ERROR_DISC;
        return false;
    }
    
    if(debug){
        printf("Disc\n");
        printf(" X: %f, Y: %f\n", disc.pos.x, disc.pos.y);
    }
    
    // validation
    if(!isCircInGameCirc(disc)){
        error = GAME_ERROR_DISC_POS;
        return false;
    }
    
    return true;
}

static bool gameFileReadEmitter(){
    char* line;
    vect_t pos;
    double alpha, flow, speed;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(
        sscanf(
            line,
            "%lf %lf %lf %lf %lf",
            &pos.x, &pos.y, &alpha, &flow, &speed
        ) < 5
    ){
        error = GAME_ERROR_EMITTER;
        return false;
    }
    
    if(debug){
        printf(
            " X: %f, Y: %f, Alpha: %f, Flow: %f, Speed: %f\n",
            pos.x, pos.y, alpha, flow, speed
        );
    }
    
    // validation
    if(alpha > MAX_ALPHA){
        error = GAME_ERROR_EMITTER_ALPHA;
        return false;
    }
    
    if(speed > MAX_VG || MIN_VG > speed){
        error = GAME_ERROR_EMITTER_SPEED;
        return false;
    }
    
    if(isVectInGameCirc(pos) || !isVectInGameRect(pos)){
        error = GAME_ERROR_EMITTER_POS;
        return false;
    }
    
    return true;
}

static bool gameFileReadEmitters(){
    char* line;
    unsigned int numbEmitters;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(sscanf(line, "%u", &numbEmitters) < 1){
        return GAME_ERROR_EMITTERS;
    }
    
    if(debug){
        printf("Emitter count: %u\n", numbEmitters);
    }
    
    // read emitters
    unsigned int i;
    for(i = 0; i < numbEmitters; i++){
        if(!gameFileReadEmitter()){
            return false;
        }
    }
    
    return true;
}

static bool gameFileReadGroup(){
    char* line;
    char buf[11];
    
    vect_t pos;
    vect_t speed;
    double omega;
    unsigned int type, numbParts;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(
        sscanf(
            line,
            "%lf %lf %lf %lf %lf %10s %u",
            &pos.x, &pos.y, &speed.x, &speed.y, &omega, buf, &numbParts
        ) < 7
    ){
        error = GAME_ERROR_GROUP;
        return false;
    }
    
    // check for valid values
    if(!strcmp(buf, "INOFFENSIF")){
        type = GROUP_TYPE_HARMLESS;
    }else if(!strcmp(buf, "DANGEREUX")){
        type = GROUP_TYPE_DANGEROUS;
    }else{
        error = GAME_ERROR_GROUPTYPE;
        return false;
    }
    
    if(debug){
        printf(
            " X: %f, Y: %f, VX: %f, VY: %f,"
            " OMEGA: %f,"
            " TYPE: %s,"
            " PARTS COUNT: %u\n",
            pos.x, pos.y, speed.x, speed.y,
            omega,
            type == GROUP_TYPE_HARMLESS ? "HARMLESS" : "DANGEROUS",
            numbParts
        );
    }
    
    // validate speed
    double speedLen = vectLength(speed);
    if(speedLen > MAX_VG || speedLen < MIN_VG){
        error = GAME_ERROR_GROUP_SPEED;
        return false;
    }
    
    // read particles
    if(numbParts > 1){
        unsigned int i;
        for(i = 0; i < numbParts; i++){
            if(!gameFileReadPart()){
                return false;
            }
        }
    }else{
        circ_t part = {
            .pos = pos,
            .r = R_PART
        };
        
        if(!isCircInGameRect(part)){
            error = GAME_ERROR_PART_POS;
            return false;
        }
    }
    
    return true;
}

static bool gameFileReadGroups(){
    char* line;
    unsigned int numbGroups;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(sscanf(line, "%u", &numbGroups) < 1){
        error = GAME_ERROR_GROUPS;
        return false;
    }
    
    if(debug){
        printf("Group count: %u\n", numbGroups);
    }
    
    unsigned int i;
    for(i = 0; i < numbGroups; i++){
        if(!gameFileReadGroup()){
            return false;
        }
    }
    
    return true;
}

static bool gameFileReadPart(){
    char* line;
    vect_t pos;
    
    if(!(line = gameFileReadLine())){
        return false;
    }
    
    if(sscanf(line, "%lf %lf", &pos.x, &pos.y) < 2){
        error = GAME_ERROR_PART;
        return false;
    }
    
    if(debug){
        printf("  X: %lf, Y: %lf\n", pos.x, pos.y);
    }
    
    circ_t part = {
        .pos = pos,
        .r = R_PART
    };
    
    if(!isCircInGameRect(part)){
        error = GAME_ERROR_PART_POS;
        return false;
    }
    
    return true;
}

bool gameFileRead(char* name){
    error = GAME_OK;
    file = NULL;
    fileName = name;
    lineNumber = 0;
    
    bool ok = true;
    
    if(!(file = fopen(fileName, "r"))){
        ok = false;
        error = GAME_ERROR_FOPEN;
    }
    
    ok = ok && gameFileReadScore();
    ok = ok && gameFileReadInterval();
    ok = ok && gameFileReadDisc();
    ok = ok && gameFileReadEmitters();
    ok = ok && gameFileReadGroups();
    
    if(file && fclose(file)){
        ok = false;
        error = GAME_ERROR_FCLOSE;
    }
    
    return ok;
}

void gamePrintError(){
    printf("\n");
    printf("ERROR in %s on line %u\n", fileName, lineNumber);
    printf(" %s\n", GAME_ERROR_MESSAGES[error]);
}

void gameSetDebug(bool flag){
    debug = flag;
}
