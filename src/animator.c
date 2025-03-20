//** me inspirei no código: https://github.com/vimichael/raylib-animations*/

#include "../include/animator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum animationType stringParaEnum(const char *str) {
    if (strcmp(str, "REPEATING") == 0) return REPEATING;
    if (strcmp(str, "ONESHOT") == 0) return ONESHOT;
    return REPEATING;
}

void criaAnimation(Animation* animacoes){
    int first, last, cur, stp;
    float durationl, anspeed;
    char antype [20];

    int i = 0;

    FILE* animdados;
    animdados = fopen("dat.txt", "r");

    for (i = 0; i < ANIMSTATESFINAL; i++){
        fscanf(animdados, "%d %d %d %f %f %d %s", &first, &last, &cur, &durationl, &anspeed, &stp, antype);
        animacoes[i] = (Animation){.first = first, .last = last, .cur = cur, .duration_left = durationl, .speed = anspeed, .step = stp, .type = stringParaEnum(antype)};
    }


    printf("%d\n", sizeof(enum animStates));

    fclose(animdados);
}



void animationupdate(Animation* self, bool* canupdt, enum animStates* anst){
    float dt = GetFrameTime();

    self->duration_left -= dt;

    if(self->type == ONESHOT)
        *canupdt = false;

    if(self->duration_left <= 0.0){
        self->duration_left = self->speed;
        self->cur += self->step;

        if(self->cur > self->last){

            switch (self->type)
            {
            case REPEATING:
                self->cur = self->first;
                break;
            case ONESHOT:
                *anst = IDLE;
                *canupdt = true;
                self->cur = self->first;
                break;
            default:
                break;
            }
            
        } else if(self->cur < self->first){
            switch (self->type)
            {
            case REPEATING:
                self->cur = self->last;
                break;
            case ONESHOT:
                *anst = IDLE;
                *canupdt = true;
                self->cur = self->last;
                break;
            default:
                break;
            }
            
        }
    }
}

Rectangle animation_frame(Animation* self, int frames_p_row, int width, int height){
    int x = (self->cur%frames_p_row) * width;
    int y = (self->cur/frames_p_row) * height;

    return (Rectangle) {.x = x, .y = y, .width=width, .height=height};
}
