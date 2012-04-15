//
//  geometry.c
//  StickyParticles
//
//  Created by Alessandro Motta on 3/23/12.
//

#include <stdbool.h>
#include <stdlib.h>

#include "circle.h"
#include "constants.h"
#include "geometry.h"
#include "particle.h"
#include "rectangle.h"
#include "vector.h"

bool isCircInRect(circ_t* circ, rect_t* rect){
    static rect_t* rectInt;
    bool valid = false;
    double radius;
    
    if(!circ || !rect) return;
    
    if(!rectInt){
        rectInt = rectNew();
    }
    
    // get radius
    radius = circGetRadius(circ);
    
    // hiiiiigh power!
    if(
       rectGetRight(rect) - rectGetLeft(rect) < radius
       || rectGetTop(rect) - rectGetBottom(rect) < radius
    ){
        return false;
    }
    
    // set up rect
    rectSetLeft(rectInt, rectGetLeft(rect) + radius);
    rectSetRight(rectInt, rectGetRight(rect) - radius);
    rectSetBottom(rectInt, rectGetBottom(rect) + radius);
    rectSetTop(rectInt, rectGetTop(rect) - radius);
    
    return isVectInRect(circGetPos(circ), rectInt);
}

bool isCircInGameRect(circ_t* circ){
    return isCircInRect(circ, getGameRect());
}

bool isPartInGameCirc(part_t* part){
    static circ_t* circ;
    bool valid = false;
    
    if(!part) return;
    
    if(!circ){
        circ = circNew();
        circSetRadius(circ, R_PART);
    }
    
    // set pos
    circSetPos(circ, partGetPos(part));
    
    // check
    valid = isCircInGameCirc(circ);
    
    // unset pos
    circSetPos(circ, NULL);
    
    return valid;
}

bool isPartInGameRect(part_t* part){
    static circ_t* circ;
    bool valid = false;
    
    if(!part) return;
    
    if(!circ){
        circ = circNew();
        circSetRadius(circ, R_PART);
    }
    
    // set pos
    circSetPos(circ, partGetPos(part));
    
    // check
    valid = isCircInGameRect(circ);
    
    // unset pos
    circSetPos(circ, NULL);
    
    return valid;
}

bool isVectInCirc(vect_t* vect, circ_t* circExt){
    static circ_t* circInt;
    bool valid = false;
    
    if(!vect || !circExt) return;
    
    if(!circInt){
        circInt = circNew();
        circSetRadius(circInt, 0);
    }
    
    // set circle position
    circSetPos(circInt, vect);
    
    // check
    valid = isCircInCirc(circInt, circExt);
    
    // unset pos
    circSetPos(circInt, NULL);
    
    return valid;
}

bool isVectInGameCirc(vect_t* vect){
    return isVectInCirc(vect, getGameCirc());
}

bool isVectInRect(vect_t* vect, rect_t* rect){
    if(!vect || !rect) return false;
    
    if(
       rectGetLeft(rect) < vectGetX(vect)
       && vectGetX(vect) < rectGetRight(rect)
       && rectGetBottom(rect) < vectGetY(vect)
       && vectGetY(vect) < rectGetTop(rect)
    ){
        return true;
    }else{
        return false;
    }
}

bool isVectInGameRect(vect_t* vect){
    return isVectInRect(vect, getGameRect());
}