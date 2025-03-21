#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

enum animationType {REPEATING, ONESHOT};

enum animStates {IDLE, WALKING, WALKINGB, PUNCHING1, PUNCHING2, PUNCHING3, ANIMSTATESFINAL};

typedef struct Animation
{
    int first;
    int last;
    int cur;
    int step;

    float speed;
    float duration_left;

    enum animationType type;

    int frame_width;
    int frame_height;

    int px;
    int py;
} Animation;

typedef struct personagens
{
    Animation* animations;
    Texture2D* textures;
} personagens;

void handle_init_loads(personagens* personagem);


void animationupdate(Animation* self, bool* canupdt,  enum animStates* anst);
void animationupdateatk(Animation* self, bool* canupdt, enum animStates* anst, Vector2* pos);
Rectangle animation_frame(Animation* self);
//Rectangle animation_frame_cammy_jump(Animation* self, int frames_p_row, int width, int height);

#endif