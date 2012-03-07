//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdio.h>
#include <stdlib.h>

#include "game.h"

static void usage(){
    printf(
        "Usage of Sticky Particles\n"
        " sticky.x file1 [file2 file3 ... fileN]\n"
    );
}

int main(int argc, char** argv){
    if(argc < 2){
        usage();
        return EXIT_SUCCESS;
    }
    
    int error;
    unsigned int i;
    for(i = 1; i < argc; i++){
        error = gameFileRead(argv[i]);
        
        if(error){
            printf("\n");
            printf("ERROR in %s\n", argv[i]);
            printf(" %s\n", gameGetError(error));
        }
    }
    
    return EXIT_SUCCESS;
}