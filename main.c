//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

static void usage();

int main(int argc, char** argv){
    if(argc < 2){
        usage();
        return EXIT_SUCCESS;
    }
    
    gameSetDebug(true);
    
    unsigned int i;
    for(i = 1; i < argc; i++){
        if(!gameFileRead(argv[i])){
            gamePrintError();
        }
    }
    
    return EXIT_SUCCESS;
}

static void usage(){
    printf(
        "Usage of Sticky Particles\n"
        " sticky.x file1 [file2 file3 ... fileN]\n"
    );
}