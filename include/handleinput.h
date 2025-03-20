#ifndef HANDLEINPUT_H
#define HANDLEINPUT_H
#include "raylib.h"
#include "animator.h"
#include <stdlib.h>
#include <stdio.h>


void handleInput(Vector2* dir, bool can_update_animation, enum animStates* animState);

#endif