#include "../include/handleinput.h"
//#include "include/animator.h"

void chstates(personagens* personagem, int state, int substate){
    personagem->animationState = state;
    personagem->animationSubState = substate;
}

void move(personagens* personagem, int direction, int state, int substate){
    personagem->direction.x = direction;
    chstates(personagem, state, substate);
    //personagem->layer = 1;
}

void attack(personagens* personagem, int state, int substate){
    chstates(personagem, state, substate);
    //personagem->layer=2;
}

void onJumping(personagens* personagem){
    //printf("%d\n", personagem->animations->cur);
   // personagem->direction.y = 1;
    personagem->velocity.x = 100;
    //printf("fac %d\n", personagem->facing);
    if(personagem->grounded) personagem->direction.x = personagem->facing;
   
}

void jump(personagens* personagem, int state, int substate){
    if(personagem->grounded){
        chstates(personagem, JUMP, JUMPING);
        personagem->velocity.y += -500;
        personagem->grounded = false;
    }
    //else personagem->direction.y = -1; 
}

void jumpf(personagens* personagem, int state, int substate){
    if(personagem->grounded){
        chstates(personagem, state, substate);
        personagem->velocity.y += -500;
        personagem->grounded = false;
        personagem->direction.x = personagem->facing;
    }
}

void inputIdle(personagens* personagem, int qual){
    
    switch (qual)
    {
    case PLAYER1:

        if(IsKeyDown(KEY_D) && IsKeyDown(KEY_W) && personagem[PLAYER1].facing == 1) jumpf(&personagem[PLAYER1], JUMP, JUMPINGF);
        else if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W) && personagem[PLAYER1].facing == -1) jumpf(&personagem[PLAYER1], JUMP, JUMPINGF);
        
        if(IsKeyDown(KEY_D)) move(&personagem[PLAYER1], 1, WALK, WALKING);
        else if(IsKeyDown(KEY_A)) move(&personagem[PLAYER1], -1, WALK, WALKINGB);

        else if(IsKeyDown(KEY_W)) jump(&personagem[PLAYER1], JUMP, JUMPING);
        
        else if(IsKeyDown(KEY_T))attack(&personagem[PLAYER1], ATTACK, PUNCHING1);
        else if(IsKeyDown(KEY_Y))attack(&personagem[PLAYER1], ATTACK, PUNCHING2);
        else if(IsKeyDown(KEY_U))attack(&personagem[PLAYER1], ATTACK, PUNCHING3);
        
        else chstates(&personagem[PLAYER1], IDLE, IDLE);
        break;
    case PLAYER2:
        if(IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP) && personagem[PLAYER2].facing == 1) jumpf(&personagem[PLAYER2], JUMP, JUMPINGF);
        else if(IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP) && personagem[PLAYER2].facing == -1) jumpf(&personagem[PLAYER2], JUMP, JUMPINGF);
        
        else if(IsKeyDown(KEY_RIGHT)) move(&personagem[PLAYER2], 1, WALK, WALKING);
        else if(IsKeyDown(KEY_LEFT)) move(&personagem[PLAYER2], -1, WALK, WALKINGB);
        else if(IsKeyDown(KEY_UP)) jump(&personagem[PLAYER2], JUMP, JUMPING);
        
        else if(IsKeyDown(KEY_KP_1)) attack(&personagem[PLAYER2], ATTACK, PUNCHING1);
        else if(IsKeyDown(KEY_KP_2)) attack(&personagem[PLAYER2], ATTACK, PUNCHING2);
        else if(IsKeyDown(KEY_KP_3)) attack(&personagem[PLAYER2], ATTACK, PUNCHING3);
        
        else chstates(&personagem[PLAYER2], IDLE, IDLE);
        
        break;
    default:
        break;
    }
}

void inputWalk(personagens* personagem, int qual){
    printf("%d %d\n", (int)personagem[PLAYER1].direction.x, personagem[PLAYER1].facing);
    if(IsKeyDown(KEY_W) && (int)personagem[PLAYER1].direction.x==personagem[PLAYER1].facing) printf("foi\n");
    //else printf("na\n");
    switch (qual)
    {
    case PLAYER1:
        if(IsKeyDown(KEY_D) && IsKeyDown(KEY_W) && personagem[PLAYER1].facing == 1) jumpf(&personagem[PLAYER1], JUMP, JUMPINGF);
        else if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W) && personagem[PLAYER1].facing == -1) jumpf(&personagem[PLAYER1], JUMP, JUMPINGF);
        
        else if(IsKeyDown(KEY_D))
            move(&personagem[PLAYER1], 1, WALK, WALKING);
        else if(IsKeyDown(KEY_A))
            move(&personagem[PLAYER1], -1, WALK, WALKINGB);


        else if(IsKeyDown(KEY_T))
            attack(&personagem[PLAYER1], ATTACK, PUNCHING1);
        else if(IsKeyDown(KEY_Y))
            attack(&personagem[PLAYER1], ATTACK, PUNCHING2);
        else if(IsKeyDown(KEY_U))
            attack(&personagem[PLAYER1], ATTACK, PUNCHING3);
        else
            chstates(&personagem[PLAYER1], IDLE, IDLE);
        
        break;
    case PLAYER2:
        if(IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP) && personagem[PLAYER2].facing == 1) jumpf(&personagem[PLAYER2], JUMP, JUMPINGF);
        else if(IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP) && personagem[PLAYER2].facing == -1) jumpf(&personagem[PLAYER2], JUMP, JUMPINGF);
        
        else if(IsKeyDown(KEY_RIGHT))
            move(&personagem[PLAYER2], 1, WALK, WALKING);
        else if(IsKeyDown(KEY_LEFT))
            move(&personagem[PLAYER2], -1, WALK, WALKINGB);

        else if(IsKeyDown(KEY_KP_1))
            attack(&personagem[PLAYER2], ATTACK, PUNCHING1);
        else if(IsKeyDown(KEY_KP_2))
            attack(&personagem[PLAYER2], ATTACK, PUNCHING2);
        else if(IsKeyDown(KEY_KP_3))
            attack(&personagem[PLAYER2], ATTACK, PUNCHING3);

        else
            chstates(&personagem[PLAYER2], IDLE, IDLE);
        
        break;
    default:
        break;
    }
}

void inputAttack(personagens* personagem, int qual){
    switch (qual)
    {
    case PLAYER1:
        if(IsKeyDown(KEY_T) && personagem[PLAYER1].animationSubState != PUNCHING1) attack(&personagem[PLAYER1], ATTACK, PUNCHING1);

        else if(IsKeyDown(KEY_Y) && personagem[PLAYER1].animationSubState != PUNCHING2) attack(&personagem[PLAYER1], ATTACK, PUNCHING2);

        else if(IsKeyDown(KEY_U) && personagem[PLAYER1].animationSubState != PUNCHING2) attack(&personagem[PLAYER1], ATTACK, PUNCHING3);

        //else chstates(&personagem[PLAYER1], IDLE, IDLE);
        
        break;

    case PLAYER2:
        if(IsKeyDown(KEY_KP_1) && personagem[PLAYER2].animationSubState != PUNCHING1) attack(&personagem[PLAYER2], ATTACK, PUNCHING1);

        else if(IsKeyDown(KEY_KP_2) && personagem[PLAYER2].animationSubState != PUNCHING2) attack(&personagem[PLAYER2], ATTACK, PUNCHING2);
        
        else if(IsKeyDown(KEY_KP_3) && personagem[PLAYER2].animationSubState != PUNCHING3) attack(&personagem[PLAYER2], ATTACK, PUNCHING3);
        
        //else chstates(&personagem[PLAYER2], IDLE, IDLE);
        
        break;
    default:
        break;
    }
}

void inputJump(personagens* personagem, int qual){
    switch (qual)
    {
    case PLAYER1:
        if(IsKeyDown(KEY_T) && personagem[PLAYER1].animationSubState != PUNCHING1) attack(&personagem[PLAYER1], ATTACK, PUNCHING1);

        else if(IsKeyDown(KEY_Y) && personagem[PLAYER1].animationSubState != PUNCHING2) attack(&personagem[PLAYER1], ATTACK, PUNCHING2);

        else if(IsKeyDown(KEY_U) && personagem[PLAYER1].animationSubState != PUNCHING2) attack(&personagem[PLAYER1], ATTACK, PUNCHING3);

        //else chstates(&personagem[PLAYER1], IDLE, IDLE);
        
        break;

    case PLAYER2:
        if(IsKeyDown(KEY_KP_1) && personagem[PLAYER2].animationSubState != PUNCHING1) attack(&personagem[PLAYER2], ATTACK, PUNCHING1);

        else if(IsKeyDown(KEY_KP_2) && personagem[PLAYER2].animationSubState != PUNCHING2) attack(&personagem[PLAYER2], ATTACK, PUNCHING2);
        
        else if(IsKeyDown(KEY_KP_3) && personagem[PLAYER2].animationSubState != PUNCHING3) attack(&personagem[PLAYER2], ATTACK, PUNCHING3);
        
        //else chstates(&personagem[PLAYER2], IDLE, IDLE);
        
        break;
    default:
        break;
    }
}

void handleInput( bool* can_update_animation, enum animStates* animState, personagens* personagem){

    for(int i = PLAYER1; i <= PLAYER2; i++){
        switch (personagem[i].animationState)
        {
        case IDLE:
            inputIdle(personagem, i);
            personagem[i].layer = 0;
            break;
        case WALK:
            inputWalk(personagem, i);
            personagem[i].layer = 1;
            break;
        case JUMP:
            onJumping(&personagem[i]);
            personagem[i].layer = 2;
            break;
        case CROUNCH:
            break;
        case ATTACK:
            inputAttack(personagem, i);
            personagem[i].layer = 3;
            break;
        default:
            break;
        }
    }
/*
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
    else if(((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))) && can_update_animation){
        dir->y = -1;
        //animState = JUMPING;
    }else if(IsKeyPressed(KEY_ONE)){
        *animState = PUNCHING1;
        
    }
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
     }*/
}