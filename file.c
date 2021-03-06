//
//  file.c
//  StickyParticles
//
//  Created by Alessandro Motta on 4/10/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "circle.h"
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
static bool fileWriteScore();
static bool fileReadInterval();
static bool fileWriteInterval();
static bool fileReadDisc();
static bool fileWriteDisc();
static bool fileReadEmitter(emitter_t* emitter);
static bool fileWriteEmitter(emitter_t* emitter);
static bool fileReadEmitters();
static bool fileWriteEmitters();
static bool fileReadGroup(group_t* group);
static bool fileReadGroups();
static bool fileWriteGroups();
static bool fileReadPart(part_t* part);
static bool fileWritePart(part_t* part);
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

static bool fileWriteScore(){
    if(!game || !file) return false;
    
    fprintf(file, "%u\n", gameGetScore(game));
    
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

static bool fileWriteInterval(){
    if(!game || !file) return false;
    
    fprintf(file, "%f\n", gameGetInterval(game));
    
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
        disc = circProjectOnCirc(disc, getGameCirc());
        
        // show warning
        printf(
            " WARNING on line %u:\n"
            "  Disc is out of game circle. Automatically corrected position\n",
            lineNumber
        );
    }
    
    gameSetDisc(game, disc);
    
    return true;
}

static bool fileWriteDisc(){
    if(!game || !file) return false;
    
    circ_t disc;
    disc = gameGetDisc(game);
    
    fprintf(file, "%f %f\n", disc.pos.x, disc.pos.y);
    
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

static bool fileWriteEmitter(emitter_t* emitter){
    if(!file) return false;
    
    // check emitter
    if(!emitter) return false;
    
    vect_t pos = emitterGetPos(emitter);
    double alpha = emitterGetAlpha(emitter);
    double flow = emitterGetFlow(emitter);
    double speed = emitterGetSpeed(emitter);
    
    fprintf(
        file,
        "%f %f %f %f %f\n",
        pos.x, pos.y, alpha, flow, speed
    );
    
    return true;
}

static bool fileReadEmitters(){
    char line[LINE_BUF_LEN];
    unsigned int numbEmitters;
    emitterSet_t* emitters = NULL;
    
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
    
    emitters = emitterSetNew(numbEmitters);
    gameSetEmitters(game, emitters);
    
    // read individual emitters
    if(!emitterSetForEach(emitters, fileReadEmitter)){
        return false;
    }
    
    return true;
}

static bool fileWriteEmitters(){
    emitterSet_t* emitters = NULL;
    
    if(!game || !file) return false;
    
    // init
    emitters = gameGetEmitters(game);
    
    fprintf(file, "\n");
    fprintf(file, "%u\n", emitterSetGetNumb(emitters));
    
    emitterSetForEach(emitters, fileWriteEmitter);
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
    if(speedLen > MAX_VG){
        // correct speed length
        speed = vectScale(speed, MAX_VG / speedLen);
        
        // show warning
        printf(
            " WARNING on line %u:\n"
            "  Group too fast. Corrected speed\n",
            lineNumber
        );
    }
    
    // read particles
    part_t* part = NULL;
    if(numbParts > 1){
        unsigned int i;
        for(i = 0; i < numbParts; i++){
            part = partNew();
            groupAdd(group, part);
            
            if(!fileReadPart(part)){
                return false;
            }
        }
    }else{
        // create new part
        part = partNew();
        groupAdd(group, part);
        
        // use same position for particle
        partSetPos(part, pos);
        
        if(!isPartInGameRect(part)){
            fileSetError(FILE_ERROR_PART_POS);
            return false;
        }
    }
    
    // config group
    groupSetPos(group, pos);
    groupSetSpeed(group, speed);
    groupSetOmega(group, omega);
    groupSetType(group, type);
    
    return true;
}

static bool fileWriteGroup(group_t* group){
    char* typeString = NULL;
    
    if(!group || !file) return false;
    
    vect_t pos = groupGetPos(group);
    vect_t speed = groupGetSpeed(group);
    double omega = groupGetOmega(group);
    int type = groupGetType(group);
    unsigned int numbParts = groupGetNumb(group);
    
    switch(type){
        case GROUP_TYPE_HARMLESS:
            typeString = "INOFFENSIF";
            break;
        default:
            typeString = "DANGEREUX";
    }
    
    fprintf(
        file,
        "%f %f %f %f %f %s %u\n",
        pos.x, pos.y,
        speed.x, speed.y,
        omega,
        typeString,
        numbParts
    );
    
    // be efficient as always!
    if(numbParts > 1){
        groupForEach(group, fileWritePart);
    }
    
    return true;
}

static bool fileReadGroups(){
    char line[LINE_BUF_LEN];
    unsigned int numbGroups;
    group_t* group = NULL;
    groupSet_t* groups = NULL;
    
    if(!fileReadLine(line, LINE_BUF_LEN)){
        return false;
    }
    
    if(sscanf(line, "%u", &numbGroups) < 1){
        fileSetError(FILE_ERROR_GROUPS);
        return false;
    }
    
    if(debug){
        printf("Group count: %u\n", numbGroups);
    }
    
    // create new groupSet
    groups = groupSetNew();
    gameSetGroups(game, groups);
    
    // read individual groups
    unsigned int i;
    for(i = 0; i < numbGroups; i++){
        group = groupNew();
        groupSetAdd(groups, group);
        
        if(!fileReadGroup(group)){
            return false;
        }
    }
    
    return true;
}

static bool fileWriteGroups(){
    groupSet_t* set = NULL;
    
    if(!game || !file) return false;
    
    // get groups
    set = gameGetGroups(game);
    
    // write numb groups
    fprintf(file, "\n");
    
    if(set){
        // write numb groups
        fprintf(file, "%u\n", groupSetGetNumb(set));
        
        // write individual groups
        groupSetForEach(set, fileWriteGroup);
    }else{
        // no groups
        fprintf(file, "0\n");
    }
    
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

static bool fileWritePart(part_t* part){
    if(!part || !file) return false;
    
    // init
    vect_t pos = partGetPos(part);
    
    // write to file
    fprintf(file, "%f %f\n", pos.x, pos.y);
    
    return true;
}

void fileSetError(int errorCode){
    error = errorCode;
}

void filePrintStatus(){
    if(error){
        printf(
            " ERROR on line %u: %s\n",
            lineNumber,
            FILE_ERROR_MESSAGES[error]
        );
    }else{
        printf(" VALID\n");
    }
}

game_t* fileRead(const char* name){
    bool ok = true;
    
    game = gameNew();
    error = FILE_OK;
    fileName = name;
    lineNumber = 0;
    
    if(debug){
        printf(
            "\n"
            "File: %s\n",
            fileName
        );
    }else{
        printf("FILE %s\n", fileName);
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
    
    if(file){
        if(fclose(file)){
            fileSetError(FILE_ERROR_FCLOSE);
        }
        
        file = NULL;
    }
    
    if(debug){
        printf("\n");
    }
    
    filePrintStatus();
    
    if(error){
        // game isn't needed anymore
        gameFree(game);
        game = NULL;
        
        // don't return pointer
        return NULL;
    }else{
        return game;
    }
}

bool fileSave(game_t* gameSave, const char* name){
    bool ok = true;
    
    // anything there?
    if(!gameSave || !name) return false;
    
    // Are we already workin'?
    if(file) return false;
    
    // prepare
    game = gameSave;
    error = FILE_OK;
    
    // open file
    file = fopen(name, "w");
    
    if(!file){
        ok = false;
        fileSetError(FILE_ERROR_FOPEN);
    }
    
    ok = ok && fileWriteScore();
    ok = ok && fileWriteInterval();
    ok = ok && fileWriteDisc();
    ok = ok && fileWriteEmitters();
    ok = ok && fileWriteGroups();
    
    if(file){
        if(fclose(file)){
            fileSetError(FILE_ERROR_FCLOSE);
        }
        
        file = NULL;
    }
    
    // free pointer
    game = NULL;
    
    if(error){
        return false;
    }else{
        return true;
    }
}

void fileSetDebug(bool flag){
    debug = flag;
}

