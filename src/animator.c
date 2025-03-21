//** me inspirei no código: https://github.com/vimichael/raylib-animations*/

#include "../include/animator.h"
#include "../include/raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    Rectangle* grupo_de_sprites_rec;
    Image* grupo_de_sprites_img;
    FILE* animdados= fopen("dat.txt", "r");
    
    //-------------------------------
    Image sprtcammy = LoadImage("assets/personagens/image.png");
    if(sprtcammy.data == NULL)
        printf("nimg");
    else   
        printf("foi\n");
    grupo_de_sprites_rec = calloc(ANIMSTATESFINAL-1, sizeof(Rectangle));
    grupo_de_sprites_img = calloc(ANIMSTATESFINAL-1, sizeof(Image));
    //animdados = fopen("../dat.txt", "r");
    if(animdados != NULL)
        printf("abriu\n");
    else
        printf("n abr\n");
    for (i = 0; i < ANIMSTATESFINAL; i++){
       
        printf("%d\n", i);
            
        
        
        printf("%d\n", i);
        fscanf(animdados, "%s %d %d %d %f %f %d %s %d %d %d %d", annome, &first, &last, &cur, &durationl, &anspeed, &stp, antype, &wid, &hei, &px, &py);
        personagem->animations[i] = (Animation){.first = first, .last = last, .cur = cur, .duration_left = durationl, .speed = anspeed, .step = stp, .type = stringParaEnum(antype), .frame_width=wid, .frame_height=hei, .px=px, .py=py};
        printf("wid = %d\n animation wid = %d\n", wid, personagem->animations[i].frame_width);
        
            
        
        
        grupo_de_sprites_rec[i] = (Rectangle){.x = px, .y = py, .width = wid*(last+1), .height=hei};
            
        
        grupo_de_sprites_img[i] = ImageFromImage(sprtcammy, grupo_de_sprites_rec[i]);
        personagem->textures[i] = LoadTextureFromImage(grupo_de_sprites_img[i]);
        
    }
    
    //printf("%d\n", sizeof(enum animStates));

    fclose(animdados);
    UnloadImage(sprtcammy);
    free(grupo_de_sprites_img);
    free(grupo_de_sprites_rec);
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

Rectangle animation_frame(Animation* self){
    int x = (self->cur%(self->last + 1)) * self->frame_width;
    int y = (self->cur/(self->last + 1)) * self->frame_height;

    return (Rectangle) {.x = x, .y = y, .width=self->frame_width, .height=self->frame_height};
}
