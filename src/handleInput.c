#include "../include/handleinput.h"
//#include "include/animator.h"


void handleInput(Vector2* dir, bool can_update_animation, enum animStates* animState){
    if(((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && can_update_animation)){
        dir->x = 1;
        *animState = WALKING;
        
    }else if (((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))) && can_update_animation)
    {
        dir->x = -1;
        *animState = WALKINGB;
        
    }else if(((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))) && can_update_animation){
        dir->y = -1;
        //animState = JUMPING;
    }else if(IsKeyPressed(KEY_P)){
        *animState = PUNCHING1;
        
    }else if(IsKeyPressed(KEY_O)){
        *animState = PUNCHING2;
    }else if(IsKeyPressed(KEY_I)){
        *animState = PUNCHING3;
    }
    else if(((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))) && can_update_animation){
        dir->y = 1;
        
    }else{
        if(can_update_animation){
            *animState = IDLE;
            
        }
    }
}