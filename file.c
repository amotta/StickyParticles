//
//  file.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "emitter.h"
#include "emitterset.h"
#include "file.h"
#include "game.h"
#include "group.h"
#include "groupset.h"
#include "particle.h"

#define LINE_BUF_LEN 81

static bool fileSkip();
static bool fileReadLine(char* buf, int bufLen);
static bool fileReadScore();
static bool fileReadInterval();
static bool fileReadDisc();
static bool fileReadEmitter(emitter_t* emitter);
static bool fileReadEmitters();
static bool fileReadGroup(group_t* group);
static bool fileReadGroups();
static bool fileReadPart(part_t* part);
static void fileSetError(int errorCode);
static void filePrintStatus();

static game_t* game;
static int error;
static bool debug;
static FILE* file;
static const char* fileName;
static unsigned int lineNumber;

enum FILE_ERROR_CODES {
    FILE_OK,
    FILE_ERROR_EOF,
    FILE_ERROR_FOPEN,
    FILE_ERROR_FGETS,
    FILE_ERROR_LINE_TOO_LONG,
    FILE_ERROR_SCORE,
    FILE_ERROR_INTERVAL,
    FILE_ERROR_INTERVAL_NEGATIVE,
    FILE_ERROR_DISC,
    FILE_ERROR_DISC_POS,
    FILE_ERROR_EMITTER,
    FILE_ERROR_EMITTER_ALPHA,
    FILE_ERROR_EMITTER_POS,
    FILE_ERROR_EMITTER_SPEED,
    FILE_ERROR_EMITTERS,
    FILE_ERROR_GROUPTYPE,
    FILE_ERROR_GROUP,
    FILE_ERROR_GROUP_SPEED,
    FILE_ERROR_GROUPS,
    FILE_ERROR_PART,
    FILE_ERROR_PART_POS,
    FILE_ERROR_FCLOSE
};

static char* FILE_ERROR_MESSAGES[] = {
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

// This function skips comments and whitespaces
// Muchas gracias to git for inspiration
static bool fileSkip(){
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
                fileSetError(FILE_ERROR_EOF);
                return false;
                
            default:
                if(!comment){
                    ungetc(c, file);
                    return true;
                }
        }
    }while(true);
}

static bool fileReadLine(char* buf, int bufLen){
    if(!fileSkip()){
        return false;
    }
    
    // level up
    lineNumber++;
    
    if(fgets(buf, bufLen, file) == NULL){
        fileSetError(FILE_ERROR_FGETS);
        return false;
    }
    
    // check if we had enough space for the entire line
    if(buf[strlen(buf) - 1] != '\n'){
        fileSetError(FILE_ERROR_LINE_TOO_LONG);
        return false;
    }
    
    // seach for comment sign
    char* comment;
    if((comment = strstr(buf, "#"))){
        *comment = '\0';
    }
    
    return true;
}

static bool fileReadScore(){
    char line[LINE_BUF_LEN];
    unsigned int score;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%u", &score) < 1){
        fileSetError(FILE_ERROR_SCORE);
        return false;
    }
    
    if(debug){
        printf("Score: %u\n", score);
    }
    
    gameSetScore(game, score);
    
    return true;
}

static bool fileReadInterval(){
    char line[LINE_BUF_LEN];
    double interval;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%lf", &interval) < 1){
        fileSetError(FILE_ERROR_INTERVAL);
        return false;
    }
    
    if(interval < 0){
        fileSetError(FILE_ERROR_INTERVAL_NEGATIVE);
        return false;
    }
    
    if(debug){
        printf("Interval: %f\n", interval);
    }
    
    gameSetInterval(game, interval);
    
    return true;
}

static bool fileReadDisc(){
    char line[LINE_BUF_LEN];
    vect_t pos;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%lf %lf", &pos.x, &pos.y) < 2){
        fileSetError(FILE_ERROR_DISC);
        return false;
    }
    
    if(debug){
        printf(
            "Disc\n"
            " X: %f, Y: %f\n", pos.x, pos.y
        );
    }
    
    circ_t disc = {
        .pos = pos,
        .r = R_DISC
    };
    
    if(!isCircInGameCirc(disc)){
        fileSetError(FILE_ERROR_DISC_POS);
        return false;
    }
    
    gameSetDisc(game, disc);
    
    return true;
}

static bool fileReadEmitter(emitter_t* emitter){
    char line[LINE_BUF_LEN];
    vect_t pos;
    double alpha, flow, speed;
    
    if(!emitter) return false;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(
        sscanf(
            line,
            "%lf %lf %lf %lf %lf",
            &pos.x, &pos.y, &alpha, &flow, &speed
        ) < 5
    ){
        fileSetError(FILE_ERROR_EMITTER);
        return false;
    }
    
    if(debug){
        printf(
            " X: %f, Y: %f, Alpha: %f, Flow: %f, Speed: %f\n",
            pos.x, pos.y, alpha, flow, speed
        );
    }
    
    // validations
    if(alpha > MAX_ALPHA){
        fileSetError(FILE_ERROR_EMITTER_ALPHA);
        return false;
    }
    
    if(speed > MAX_VG || MIN_VG > speed){
        fileSetError(FILE_ERROR_EMITTER_SPEED);
        return false;
    }
    
    if(isVectInGameCirc(pos) || !isVectInGameRect(pos)){
        fileSetError(FILE_ERROR_EMITTER_POS);
        return false;
    }
    
    emitterSetPos(emitter, pos);
    emitterSetAlpha(emitter, alpha);
    emitterSetFlow(emitter, flow);
    emitterSetSpeed(emitter, speed);
    
    return true;
}

static bool fileReadEmitters(){
    char line[LINE_BUF_LEN];
    unsigned int numbEmitters;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%u", &numbEmitters) < 1){
        fileSetError(FILE_ERROR_EMITTERS);
        return false;
    }
    
    if(debug){
        printf("Emitter count: %u\n", numbEmitters);
    }
    
    emitterSet_t* emitters = emitterSetNew(numbEmitters);
    
    // read individual emitters
    if(!emitterSetForEach(emitters, fileReadEmitter)){
        return false;
    }
    
    gameSetEmitters(game, emitters);
    
    return true;
}

static bool fileReadGroup(group_t* group){
    char buf[11];
    char line[LINE_BUF_LEN];
    vect_t pos;
    vect_t speed;
    double omega;
    unsigned int type;
    unsigned int numbParts;
    
    if(!group) return false;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(
        sscanf(
            line,
            "%lf %lf %lf %lf %lf %10s %u",
            &pos.x, &pos.y, &speed.x, &speed.y, &omega, buf, &numbParts
        ) < 7
    ){
        fileSetError(FILE_ERROR_GROUP);
        return false;
    }
    
    // check for valid values
    if(!strcmp(buf, "INOFFENSIF")){
        type = GROUP_TYPE_HARMLESS;
    }else if(!strcmp(buf, "DANGEREUX")){
        type = GROUP_TYPE_DANGEROUS;
    }else{
        fileSetError(FILE_ERROR_GROUPTYPE);
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
    double speedLen = vectLen(speed);
    if(speedLen > MAX_VG || speedLen < MIN_VG){
        fileSetError(FILE_ERROR_GROUP_SPEED);
        return NULL;
    }
    
    groupSetPos(group, pos);
    groupSetSpeed(group, speed);
    groupSetOmega(group, omega);
    groupSetType(group, type);
    
    // read particles
    if(numbParts > 1){
        unsigned int i;
        part_t* part = NULL;
        
        for(i = 0; i < numbParts; i++){
            part = partNew();
            
            if(fileReadPart(part)){
                groupAdd(group, part);
            }else{
                return false;
            }
        }
    }else{
        // create new part
        part_t* part = partNew();
        partSetPos(part, pos);
        
        if(!isPartInGameRect(part)){
            fileSetError(FILE_ERROR_PART_POS);
            return false;
        }
        
        groupAdd(group, part);
    }
    
    return true;
}

static bool fileReadGroups(){
    char line[LINE_BUF_LEN];
    unsigned int numbGroups;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%u", &numbGroups) < 1){
        error = FILE_ERROR_GROUPS;
        return false;
    }
    
    if(debug){
        printf("Group count: %u\n", numbGroups);
    }
    
    int i;
    group_t* group = NULL;
    groupSet_t* groups = groupSetNew();
    
    for(i = 0; i < numbGroups; i++){
        group = groupNew();
        
        if(fileReadGroup(group)){
            groupSetAdd(groups, group);
        }else{
            return false;
        }
    }
    
    gameSetGroups(game, groups);
    
    return true;
}

static bool fileReadPart(part_t* part){
    char line[LINE_BUF_LEN];
    vect_t pos;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%lf %lf", &pos.x, &pos.y) < 2){
        fileSetError(FILE_ERROR_PART);
        return false;
    }
    
    if(debug){
        printf("  X: %lf, Y: %lf\n", pos.x, pos.y);
    }
    
    // set pos
    partSetPos(part, pos);
    
    if(!isPartInGameRect(part)){
        fileSetError(FILE_ERROR_PART_POS);
        return false;
    }
    
    return true;
}

void fileSetError(int errorCode){
    error = errorCode;
}

void filePrintStatus(){
    printf("FILE %s\n", fileName);
    
    if(error){
        printf(
            " ERROR on line %u: %s\n", lineNumber, FILE_ERROR_MESSAGES[error]
        );
    }else{
        printf(" VALID\n");
    }
}

game_t* fileRead(const char* name){
    bool ok = true;
    
    gameFree(game);
    game = gameNew();
    
    error = FILE_OK;
    fileName = name;
    lineNumber = 0;
    
    if(debug){
        printf(
            "\n"
            "File: %s\n", fileName
        );
    }
    
    // try to open file
    file = fopen(fileName, "r");
    
    if(!file){
        ok = false;
        fileSetError(FILE_ERROR_FOPEN);
    }
    
    ok = ok && fileReadScore();
    ok = ok && fileReadInterval();
    ok = ok && fileReadDisc();
    ok = ok && fileReadEmitters();
    ok = ok && fileReadGroups();
    
    if(file && fclose(file)){
        fileSetError(FILE_ERROR_FCLOSE);
    }
    
    if(debug){
        printf("\n");
    }
    
    filePrintStatus();
    
    if(error){
        return NULL;
    }else{
        return game;
    }
}

void fileSetDebug(bool flag){
    debug = flag;
}

