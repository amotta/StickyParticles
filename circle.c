//
//  circle.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/4/12.
//

#include <math.h>

#include "circle.h"

extern bool isCircleInCircle(double circInt[], double circExt[]){
    if(circInt[CIRCLE_R] > circExt[CIRCLE_R]){
        return false;
    }
    
    double centerDistSquare = 0;
    centerDistSquare += pow(circInt[CIRCLE_X] - circExt[CIRCLE_X], 2);
    centerDistSquare += pow(circInt[CIRCLE_Y] - circExt[CIRCLE_Y], 2);
    
    if(centerDistSquare > pow(circExt[CIRCLE_R] - circInt[CIRCLE_R], 2)){
        return false;
    }else{
        return true;
    }
}
