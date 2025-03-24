#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

enum animationType {REPEATING, ONESHOT};

enum players {PLAYER1, PLAYER2};

enum animStates {IDLE, WALK, JUMP, CROUNCH, ATTACK};
enum animSubStates {IDLING, WALKING, WALKINGB, PUNCHING1, PUNCHING2, PUNCHING3, ANIMSTATESFINAL};
enum nFrmsAnim {nfIDLE = 5, nfWALKING = 6, nfJUMPING = 6};

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

typedef struct animation2
{
    int frames;
    int inicio;
}animation2;


typedef struct personagens
{
    Animation* animations;
    Texture2D* textures;
    Texture2D texture; 
    Rectangle* retangulos;
    animation2 anim2[ANIMSTATESFINAL -1];
    int type;
    int animationState;
    int animationSubState;
    int layer;
    Vector2 position;
    Vector2 direction;
} personagens;



void handle_init_loads(personagens* personagem);


void animationupdate(personagens* self, bool* canupdt,  enum animStates* anst);
void animationupdateatk(Animation* self, bool* canupdt, enum animStates* anst, Vector2* pos);
Rectangle animation_frame(Animation* self, int type);
//Rectangle animation_frame_cammy_jump(Animation* self, int frames_p_row, int width, int height);

void drawAnychar(personagens* self, enum animStates* animState, Vector2* pos, int type);


#endif