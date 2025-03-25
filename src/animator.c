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
    if (strcmp(str, "HOLDING") == 0) return HOLDING;

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

void nhandle_init_loads(personagens* personagem, enum animStates* animState){

        personagem->texture = LoadTexture("assets/personagens/old/image - Copia (2).png");

        int ii = 0;
    
        personagem->retangulos[ii] =(Rectangle){5 , 31, 47, 82}; 
        ii++;
        personagem->retangulos[ii] =(Rectangle){59, 30, 47, 83};
        ii++;
        personagem->retangulos[ii] =(Rectangle){111, 29, 47, 84};
        ii++;
        personagem->retangulos[ii] =(Rectangle){164, 30, 47, 83};
        ii++;
        personagem->retangulos[ii] =(Rectangle){217, 31, 47, 82};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {271, 26, 44, 87};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {322, 31, 41, 82};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {372, 29, 41, 84};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {420, 26, 45, 87};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {474, 31, 42, 82};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {524, 29, 41, 84};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {572, 39, 47, 74};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {670, 12, 35, 101};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {711, 25, 29, 70};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {745, 33, 33, 48};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {786, 18, 31, 78};
        ii++;
        personagem->retangulos[ii] =(Rectangle) {826, 9, 35, 104};

    
}

void drawAnychar(personagens* self, enum animStates* animState){
    
    DrawTexturePro(self->textures[self->animationSubState], animation_frame(&self->animations[self->animationSubState], self->facing), (Rectangle){self->position.x, self->position.y, self->animations[self->animationSubState].frame_width, self->animations[self->animationSubState].frame_height}, (Vector2){self->animations[self->animationSubState].frame_width / 2, self->animations[self->animationSubState].frame_height}, 0.0f, WHITE);
    //printf("desenhando %d\n", animState);
}

void animationupdate(personagens* self, bool* canupdt,  enum animStates* anst){
    float dt = GetFrameTime();
    //printf("%d\n", self[PLAYER1].animations[self[PLAYER1].animationSubState].type);
    for(int i = PLAYER1; i <= PLAYER2; i++){
        //if(i == PLAYER1) printf("%d\n", self[i].animations->cur);
        self[i].animations[self[i].animationSubState].duration_left -= dt;

        if(self[i].animations[self[i].animationSubState].type == ONESHOT)
            canupdt[i] = false;
        //self[i].animationSubState
        if(self[i].animations[self[i].animationSubState].duration_left <= 0.0){
            self[i].animations[self[i].animationSubState].duration_left = self[i].animations[self[i].animationSubState].speed;
            self[i].animations[self[i].animationSubState].cur += self[i].animations[self[i].animationSubState].step;

            if(self[i].animations[self[i].animationSubState].cur > self[i].animations[self[i].animationSubState].last){
                self[i].velocity.x = (self[i].velocity.x != 100.0f) ? 100.0f : 100.0f;

                switch (self[i].animations[self[i].animationSubState].type)
                {
                case REPEATING:
                    self[i].animations[self[i].animationSubState].cur = self[i].animations[self[i].animationSubState].first;
                    break;
                case ONESHOT:
                    self[i].animations[self[i].animationSubState].cur = self[i].animations[self[i].animationSubState].first;
                    canupdt[i] = true;
                    self[i].animationSubState = IDLE;
                    self[i].animationState = IDLE;
                    break;
                case HOLDING:
                    self[i].animations[self[i].animationSubState].cur = self[i].animations[self[i].animationSubState].last;
                    
                    break;
                default:
                    break;
                }

                
                
            } else if(self[i].animations[self[i].animationSubState].cur < self[i].animations[self[i].animationSubState].first){
                switch (self[i].animations[self[i].animationSubState].type)
                {
                case REPEATING:
                    self[i].animations[self[i].animationSubState].cur = self[i].animations[self[i].animationSubState].last;
                    break;
                case ONESHOT:
                    self[i].animations[self[i].animationSubState].cur = self[i].animations[self[i].animationSubState].last;
                    canupdt[i] = true;
                    self[i].animationSubState = IDLE;
                    self[i].animationState = IDLE;
                    break;
                case HOLDING:
                    self[i].animations[self[i].animationSubState].cur = self[i].animations[self[i].animationSubState].first;
                    break;
                default:
                    break;
                }
                
            }
        }
    }
}

Rectangle animation_frame(Animation* self, int facing){
    int nWid = self->frame_width;
    nWid *= facing; 
    int x = (self->cur%(self->last + 1)) *  self->frame_width;
    int y = (self->cur/(self->last + 1)) * self->frame_height;


    return (Rectangle) {.x = x, .y = y, .width=nWid, .height=self->frame_height};
}


