#include "include/raylib.h"
#include "include/animator.h"
#include "include/handleinput.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum frmsprw {fIDLE = 5, fWALKING = 6, fWALKINGB = 6, fJUMPING, fPUNCHING1 = 3, fPUNCHING2 = 3, fPUNCHING3 = 5};
enum frmswds {wIDLE = 47, wWALKINGs = 47, wPUNCHINGs = 77};
enum frmshts {hIDLE = 84, hWALKINGs = 87, hPUNCHINGs = 90};

int main(void)
{
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);   


    Texture2D ota = LoadTexture("assets/personagens/ota.png");


    personagens cammy;
    cammy.animations = calloc(ANIMSTATESFINAL - 1, sizeof(Animation));
    cammy.textures = calloc(ANIMSTATESFINAL-1, sizeof(Texture2D));
    

    handle_init_loads(&cammy);

    float speed = 100.0f;

    Vector2 pos = {.x = 10, .y=10};
    Vector2 dir = {.x=0, .y=0};

    Camera2D camera;
    camera.target = (Vector2){ pos.x + 20.0f, pos.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    enum animStates animState;
    Rectangle atkRec, enemy = {120, 150, 47, 84}, colRec, colRec2;

    int vida = 100 * 30;
    
    printf("%d\n", vida);

    bool can_update_animation = true;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();

        handleInput(&dir, can_update_animation, &animState);
    
        animationupdate(&cammy.animations[animState], &can_update_animation, &animState);
        
        if(CheckCollisionRecs(colRec2, enemy) && dir.x == 1)
            dir.x = 0;

        pos.x += dir.x * speed * dt;
        pos.y += dir.y * speed * dt;

        camera.target = (Vector2){ pos.x + 20, pos.y - 40 };

        dir = (Vector2){.x=0, .y=0};

        if (CheckCollisionRecs(atkRec, enemy)){
            vida -= 5;
            printf("%d\n", vida);
        }
       
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(camera);

        //DrawRectangleRec(enemy, RED);

        DrawTexturePro(ota, (Rectangle){0,0,-47,84}, enemy, (Vector2){0,0}, 0.0f, WHITE);

        DrawTexturePro(cammy.textures[animState], animation_frame(&cammy.animations[animState]), (Rectangle){pos.x, pos.y, cammy.animations[animState].frame_width, cammy.animations[animState].frame_height}, (Vector2){cammy.animations[animState].frame_width / 2, cammy.animations[animState].frame_height}, 0.0f, WHITE);

        
        
        DrawCircle(pos.x, pos.y, 10.0, WHITE);

        EndMode2D();

        //DrawTexturePro(cammyidl, animation_frame(&ancammyidl, 5), (Rectangle){10, 10, 100, 100}, (Vector2){0,0}, 0.0f, WHITE);
        
        EndDrawing();
   
    }
    free(cammy.animations);
    free(cammy.textures);
    CloseWindow();       

    return 0;
}
