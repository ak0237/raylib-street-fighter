//** me inspirei no código: https://github.com/vimichael/raylib-animations*/

#include "../include/animator.h"
#include "../include/raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

enum animationType stringParaEnum(const char *str) {
    if (strcmp(str, "REPEATING") == 0) return REPEATING;
    if (strcmp(str, "ONESHOT") == 0) return ONESHOT;
    return REPEATING;
}

void handle_init_loads(personagens* personagem){
    // variáveis do file
    int first, last, cur, stp, wid, hei, px, py;
    float durationl, anspeed;
    char antype [20], annome[20];
    //--------------------------------
    int i = 0;
    Rectangle* grupo_de_sprites_rec= malloc((ANIMSTATESFINAL) * sizeof(Rectangle));
    Image* grupo_de_sprites_img=malloc((ANIMSTATESFINAL) * sizeof(Image));
    FILE* animdados= fopen("dat.txt", "r");
    
    //-------------------------------
    Image sprtcammy = LoadImage("assets/personagens/image.png");
    if(sprtcammy.data == NULL){
        printf("imagem não loadada\n");
    }else   
        printf("foi\n");

    //animdados = fopen("../dat.txt", "r");
    if(animdados != NULL)
        printf("abriu\n");
    else
        printf("sla\n");
    for (i = 0; i < ANIMSTATESFINAL; i++){
       
        //printf("%d\n", i);
       
        //printf("%d\n", i);
        fscanf(animdados, "%s %d %d %d %f %f %d %s %d %d %d %d", annome, &first, &last, &cur, &durationl, &anspeed, &stp, antype, &wid, &hei, &px, &py);
        
        personagem->animations[i] = (Animation){.first = first, .last = last, .cur = cur, .duration_left = durationl, .speed = anspeed, .step = stp, .type = stringParaEnum(antype), .frame_width=wid, .frame_height=hei, .px=px, .py=py};
        //printf("wid = %d\n animation wid = %d\n", wid, personagem->animations[i].frame_width);
        
            
        
        
        grupo_de_sprites_rec[i] = (Rectangle){.x = px, .y = py, .width = wid*(last+1), .height=hei};
            
        
        grupo_de_sprites_img[i] = ImageFromImage(sprtcammy, grupo_de_sprites_rec[i]);
        personagem->textures[i] = LoadTextureFromImage(grupo_de_sprites_img[i]);
        
    }
    
    //printf("%d\n", sizeof(enum animStates));

    fclose(animdados);
    UnloadImage(sprtcammy);
    for(i = 0; i < ANIMSTATESFINAL; i++){
        UnloadImage(grupo_de_sprites_img[i]);
    }
    free(grupo_de_sprites_img);
    free(grupo_de_sprites_rec);
}

void drawAnychar(personagens* self, enum animStates animState, Vector2 pos){
    
    DrawTexturePro(self->textures[animState], animation_frame(&self->animations[animState], self->type), (Rectangle){pos.x, pos.y, self->animations[animState].frame_width, self->animations[animState].frame_height}, (Vector2){self->animations[animState].frame_width / 2, self->animations[animState].frame_height}, 0.0f, WHITE);
    //printf("desenhando \n");
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

Rectangle animation_frame(Animation* self, int type){
    int nWid = self->frame_width;
    if(type == 0){
        nWid = nWid * (-1);
    }
    int x = (self->cur%(self->last + 1)) *  self->frame_width;
    int y = (self->cur/(self->last + 1)) * self->frame_height;

    return (Rectangle) {.x = x, .y = y, .width=nWid, .height=self->frame_height};
}


