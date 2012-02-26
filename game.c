//
//  game.c
//  StickyParticles
//
//  Created by Alessandro Motta on 2/23/12.
//

#include <stdbool.h>
#include <stdio.h>

#include "game.h"

static int gameFileSkip(FILE* file){
    char c;
    bool comment = false;
    bool separation = false;
    
    do{
        c = fgetc(file);
        
        switch(c){
            case ' ':
            case '\t':
                separation = true;
                break;
            
            case '#':
                comment = true;
                break;
            
            case '\r':
            case '\n':
                comment = false;
                separation = true;
                break;
                
            case EOF:
                printf("ERROR: Unexpected end-of-file\n");
                return 2;
                break;
                
            default:
                if(!comment){
                    if(separation){
                        ungetc(c, file);
                        return 0;
                    }else{
                        printf("ERROR: Invalid character\n");
                        return 1;
                    }
                }
        }
    }while(true);
}

static int gameFileReadScore(FILE* file){
    unsigned int score;
    while(fscanf(file, "%u", &score) < 1){
        if(gameFileSkip(file)){
            return 1;
        }
    }
    
    printf("Score read: %u\n", score);
    
    return 0;
}

extern int gameFileRead(char* name){
    FILE* file = NULL;
    
    file = fopen(name, "r");
    if(!file){
        printf("ERROR: Could not open file\n");
        return 1;
    }
    
    gameFileReadScore(file);
    
    fclose(file);
    
    return 0;
}
