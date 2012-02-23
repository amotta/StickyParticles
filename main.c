//
//  main.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdio.h>
#include <stdlib.h>

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

    while(++argv, --argc){
        printf("%s\n", *argv);
    }
    
    return EXIT_SUCCESS;
}