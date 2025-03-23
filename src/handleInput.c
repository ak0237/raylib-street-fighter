#include "../include/handleinput.h"
//#include "include/animator.h"


void handleInput(Vector2* dir, bool* can_update_animation, enum animStates* animState){
    if((IsKeyDown(KEY_D)  && can_update_animation[PLAYER1]) ){
        dir[PLAYER1].x = 1;
        animState[PLAYER1] = WALKING;
        //printf("p1 dir\n");
    }
    else if ((IsKeyDown(KEY_A) ) && can_update_animation[PLAYER1])
    {
        dir[PLAYER1].x = -1;
        animState[PLAYER1] = WALKINGB;
        //printf("p1 lft\n");
    }
    else{
        if(can_update_animation[PLAYER1]){
            animState[PLAYER1] = IDLE;
        }
    }
    if(IsKeyDown(KEY_RIGHT) && can_update_animation[PLAYER2]){
        dir[PLAYER2].x = 1;
        animState[PLAYER2] = WALKING;
        //printf("p2 dir\n");
    }
    else if(IsKeyDown(KEY_LEFT) && can_update_animation[PLAYER2]){
        dir[PLAYER2].x = -1;
        animState[PLAYER2] = WALKINGB;
        //printf("p2 lft\n");
    }else{
        if(can_update_animation[PLAYER2]){
            animState[PLAYER2] = IDLE;
        }
    }
    /*else if(((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))) && can_update_animation){
        dir->y = -1;
        //animState = JUMPING;
    }else if(IsKeyPressed(KEY_ONE)){
        *animState = PUNCHING1;
        
    }*/
   if(IsKeyPressed(KEY_P)){
       animState[PLAYER1] = PUNCHING1;
   }
   if(IsKeyPressed(KEY_O)){
        animState[PLAYER1] = PUNCHING2;
    }
    if(IsKeyPressed(KEY_I)){
        animState[PLAYER1] = PUNCHING3;
    }

    if(IsKeyPressed(KEY_KP_1)){
        animState[PLAYER2] = PUNCHING1;
    }
    if(IsKeyPressed(KEY_KP_2)){
         animState[PLAYER2] = PUNCHING2;
     }
     if(IsKeyPressed(KEY_KP_3)){
         animState[PLAYER2] = PUNCHING3;
     }
}