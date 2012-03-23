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
static bool gameFileReadLine(char* buf, int bufLen);
static bool gameFileReadScore();
static bool gameFileReadInterval();
static bool gameFileReadDisc();
static bool gameFileReadEmitter();
static bool gameFileReadEmitters();
static bool gameFileReadGroup();
static bool gameFileReadGroups();
static bool gameFileReadPart();
static void gameSetError(int errorCode);
static void gamePrintStatus();

enum GAME_ERROR_CODES {
    GAME_OK,
    GAME_ERROR_EOF,
    GAME_ERROR_FOPEN,
    GAME_ERROR_FGETS,
    GAME_ERROR_LINE_TOO_LONG,
    GAME_ERROR_SCORE,
    GAME_ERROR_INTERVAL,
    GAME_ERROR_INTERVAL_NEGATIVE,
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
    "Time interval is negative",
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
                gameSetError(GAME_ERROR_EOF);
                return false;
                
            default:
                if(!comment){
                    ungetc(c, file);
                    return true;
                }
        }
    }while(true);
}

static bool gameFileReadLine(char* buf, int bufLen){
    if(!gameFileSkip()){
        return false;
    }
    
    // level up
    lineNumber++;
    
    if(fgets(buf, bufLen, file) == NULL){
        gameSetError(GAME_ERROR_FGETS);
        return false;
    }
    
    // check if we had enough space for the entire line
    if(buf[strlen(buf) - 1] != '\n'){
        gameSetError(GAME_ERROR_LINE_TOO_LONG);
        return false;
    }
    
    // seach for comment sign
    char* comment;
    if((comment = strstr(buf, "#"))){
        *comment = '\0';
    }
    
    return true;
}

static bool gameFileReadScore(){
    char line[LINE_BUF_LEN];
    unsigned int score;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%u", &score) < 1){
        gameSetError(GAME_ERROR_SCORE);
        return false;
    }
    
    if(debug){
        printf("Score: %u\n", score);
    }
    
    return true;
}

static bool gameFileReadInterval(){
    char line[LINE_BUF_LEN];
    double interval;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%lf", &interval) < 1){
        gameSetError(GAME_ERROR_INTERVAL);
        return false;
    }
    
    if(interval < 0){
        gameSetError(GAME_ERROR_INTERVAL_NEGATIVE);
        return false;
    }
    
    if(debug){
        printf("Interval: %f\n", interval);
    }
    
    return true;
}

static bool gameFileReadDisc(){
    char line[LINE_BUF_LEN];
    vect_t pos;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%lf %lf", &pos.x, &pos.y) < 2){
        gameSetError(GAME_ERROR_DISC);
        return false;
    }
    
    if(debug){
        printf(
            "Disc\n"
            " X: %f, Y: %f\n", pos.x, pos.y
        );
    }
    
    // validation
    circ_t disc = {
        .pos = pos,
        .r = R_DISC
    };
    
    if(!isCircInGameCirc(disc)){
        gameSetError(GAME_ERROR_DISC_POS);
        return false;
    }
    
    return true;
}

static bool gameFileReadEmitter(){
    char line[LINE_BUF_LEN];
    vect_t pos;
    double alpha, flow, speed;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(
        sscanf(
            line,
            "%lf %lf %lf %lf %lf",
            &pos.x, &pos.y, &alpha, &flow, &speed
        ) < 5
    ){
        gameSetError(GAME_ERROR_EMITTER);
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
        gameSetError(GAME_ERROR_EMITTER_ALPHA);
        return false;
    }
    
    if(speed > MAX_VG || MIN_VG > speed){
        gameSetError(GAME_ERROR_EMITTER_SPEED);
        return false;
    }
    
    if(isVectInGameCirc(pos) || !isVectInGameRect(pos)){
        gameSetError(GAME_ERROR_EMITTER_POS);
        return false;
    }
    
    return true;
}

static bool gameFileReadEmitters(){
    char line[LINE_BUF_LEN];
    unsigned int numbEmitters;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%u", &numbEmitters) < 1){
        gameSetError(GAME_ERROR_EMITTERS);
        return false;
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
    char buf[11];
    char line[LINE_BUF_LEN];
    
    vect_t pos;
    vect_t speed;
    double omega;
    unsigned int type, numbParts;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(
        sscanf(
            line,
            "%lf %lf %lf %lf %lf %10s %u",
            &pos.x, &pos.y, &speed.x, &speed.y, &omega, buf, &numbParts
        ) < 7
    ){
        gameSetError(GAME_ERROR_GROUP);
        return false;
    }
    
    // check for valid values
    if(!strcmp(buf, "INOFFENSIF")){
        type = GROUP_TYPE_HARMLESS;
    }else if(!strcmp(buf, "DANGEREUX")){
        type = GROUP_TYPE_DANGEROUS;
    }else{
        gameSetError(GAME_ERROR_GROUPTYPE);
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
        gameSetError(GAME_ERROR_GROUP_SPEED);
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
            gameSetError(GAME_ERROR_PART_POS);
            return false;
        }
    }
    
    return true;
}

static bool gameFileReadGroups(){
    char line[LINE_BUF_LEN];
    unsigned int numbGroups;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
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
    char line[LINE_BUF_LEN];
    vect_t pos;
    
    if(!gameFileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%lf %lf", &pos.x, &pos.y) < 2){
        gameSetError(GAME_ERROR_PART);
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
        gameSetError(GAME_ERROR_PART_POS);
        return false;
    }
    
    return true;
}

bool gameFileRead(char* name){
    bool ok = true;
    
    error = GAME_OK;
    fileName = name;
    file = fopen(fileName, "r");
    lineNumber = 0;
    
    if(debug){
        printf(
            "\n"
            "File: %s\n",   fileName
        );
    }
    
    if(!file){
        ok = false;
        gameSetError(GAME_ERROR_FOPEN);
    }
    
    ok = ok && gameFileReadScore();
    ok = ok && gameFileReadInterval();
    ok = ok && gameFileReadDisc();
    ok = ok && gameFileReadEmitters();
    ok = ok && gameFileReadGroups();
    
    if(file && fclose(file)){
        gameSetError(GAME_ERROR_FCLOSE);
    }
    
    if(debug){
        printf("\n");
    }
    
    gamePrintStatus();
    
    if(error){
        return false;
    }else{
        return true;
    }
}
       
void gameSetError(int errorCode){
    error = errorCode;
}

void gamePrintStatus(){
    printf("FILE %s\n", fileName);
    
    if(error){
        printf(
            " ERROR on line %u: %s\n", lineNumber, GAME_ERROR_MESSAGES[error]
        );
    }else{
        printf(" VALID\n");
    }
}

void gameSetDebug(bool flag){
    debug = flag;
}
