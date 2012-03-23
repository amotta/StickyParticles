//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "game.h"
}

static void usage();
static bool isOpt(char* arg);
static void handleOpt(char* arg);

int main(int argc, char** argv){
    int i;
    
    if(argc < 2){
        usage();
        return EXIT_SUCCESS;
    }
    
    for(i = 1; i < argc; i++){
        if(isOpt(argv[i])){
            handleOpt(argv[i]);
        }else{
            gameFileRead(argv[i]);
        }
    }
    
    return EXIT_SUCCESS;
}

static bool isOpt(char* arg){
    if(arg[0] == '-'){
        return true;
    }else{
        return false;
    }
}

static void handleOpt(char* arg){
    if(!strcmp("-v", arg)){
        gameSetDebug(true);
    }else if(!strcmp("-s", arg)){
        gameSetDebug(false);
    }
}

static void usage(){
    printf(
        "Usage of Sticky Particles\n"
        " sticky.x file1 [file2 ... fileN]\n"
        " -v    Activate debugging\n"
        " -s    Deactivate debugging\n"
    );
}