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

   /* Image sprtcammy = LoadImage("assets/personagens/image.png");


    Rectangle idlsprtcammy = {.x = 0, .y = 0, .width=wIDLE*fIDLE, .height=hIDLE};
    Rectangle wlksprtcammy = {.x = 0, .y = 84, .width = wWALKINGs*fWALKING, .height=hWALKINGs};
    Rectangle pun1sprtcammy= {.x=0, .y = 87+84, .width = wPUNCHINGs*fPUNCHING1, .height=hPUNCHINGs};
    Rectangle pun2sprtcammy= {.x=pun1sprtcammy.width, .y = pun1sprtcammy.y, .width = wPUNCHINGs*fPUNCHING2, .height=hPUNCHINGs};
    Rectangle pun3sprtcammy= {.x=pun1sprtcammy.width + pun2sprtcammy.width, .y = pun1sprtcammy.y, .width = wPUNCHINGs*fPUNCHING3, .height=hPUNCHINGs};
    //Rectangle jmpsprtcammy = {.x = 670, .y=8, .width = 193, .height = 105};

    Image sprtidlcammy = ImageFromImage(sprtcammy, idlsprtcammy);
    Image sprtwlkcammy = ImageFromImage(sprtcammy, wlksprtcammy);
    Image sprtpun1cammy= ImageFromImage(sprtcammy, pun1sprtcammy);
    Image sprtpun2cammy= ImageFromImage(sprtcammy, pun2sprtcammy);
    Image sprtpun3cammy= ImageFromImage(sprtcammy, pun3sprtcammy);
    //Image sprtjmpcammy = ImageFromImage(sprtcammy, jmpsprtcammy);

    */

    

    Texture2D ota = LoadTexture("assets/personagens/ota.png");
/*
    Texture2D cammyidl = LoadTextureFromImage(sprtidlcammy);
    Texture2D cammywlk = LoadTextureFromImage(sprtwlkcammy);
    Texture2D cammypun1= LoadTextureFromImage(sprtpun1cammy);
    Texture2D cammypun2= LoadTextureFromImage(sprtpun2cammy);
    Texture2D cammypun3= LoadTextureFromImage(sprtpun3cammy);
   // Texture2D cammyjmp = LoadTextureFromImage(sprtjmpcammy);*/

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
        // Draw
        //----------------------------------------------------------------------------------

        if (CheckCollisionRecs(atkRec, enemy)){
            vida -= 5;
            printf("%d\n", vida);
        }
       
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(camera);

        //DrawRectangleRec(enemy, RED);

        DrawTexturePro(ota, (Rectangle){0,0,-47,84}, enemy, (Vector2){0,0}, 0.0f, WHITE);

        switch (animState)
        {
        case WALKING:
            colRec = (Rectangle){pos.x, pos.y,  wWALKINGs, hWALKINGs};
            colRec2 = (Rectangle){pos.x - 17, pos.y - hWALKINGs,  22, 81};
            DrawTexturePro(cammy.textures[WALKING], animation_frame(&cammy.animations[WALKING]), colRec, (Vector2){wWALKINGs/2 ,hWALKINGs}, 0.0f, WHITE);
            DrawRectangleLinesEx(colRec2, 2.0, BLACK);
            break;
        case WALKINGB:
            colRec2 = (Rectangle){pos.x - 17, pos.y - hWALKINGs,  22, 81};
            DrawTexturePro(cammy.textures[WALKING], animation_frame(&cammy.animations[WALKINGB]), (Rectangle){pos.x, pos.y,  wWALKINGs, hWALKINGs}, (Vector2){wWALKINGs/2 ,hWALKINGs}, 0.0f, WHITE);
            DrawRectangleLinesEx(colRec2, 2.0, BLACK);
            break;
        case PUNCHING1:
            DrawTexturePro(cammy.textures[PUNCHING1], animation_frame(&cammy.animations[PUNCHING1]), (Rectangle){pos.x, pos.y, wPUNCHINGs, hPUNCHINGs}, (Vector2){wPUNCHINGs/2 ,hPUNCHINGs}, 0.0f, WHITE);
            //DrawRectangleGradientEx(atkRec, RED, BLUE, GREEN, PURPLE);
            break;
        case PUNCHING2:
            DrawTexturePro(cammy.textures[PUNCHING2], animation_frame(&cammy.animations[PUNCHING2]), (Rectangle){pos.x, pos.y, wPUNCHINGs, hPUNCHINGs}, (Vector2){wPUNCHINGs/2 ,hPUNCHINGs}, 0.0f, WHITE);
            break;
        case PUNCHING3:
            DrawTexturePro(cammy.textures[PUNCHING3], animation_frame(&cammy.animations[PUNCHING3]), (Rectangle){pos.x, pos.y, wPUNCHINGs, hPUNCHINGs}, (Vector2){wPUNCHINGs/2 ,hPUNCHINGs}, 0.0f, WHITE);
            break;
        case IDLE:
            colRec2 = (Rectangle){pos.x - 17, pos.y - hWALKINGs,  22, 81};
            DrawTexturePro(cammy.textures[IDLE], animation_frame(&cammy.animations[IDLE]), (Rectangle){pos.x, pos.y, cammy.animations[IDLE].frame_width, cammy.animations[IDLE].frame_height}, (Vector2){cammy.animations[IDLE].frame_width/2 ,cammy.animations[IDLE].frame_height}, 0.0f, WHITE);
            DrawRectangleLinesEx(colRec2, 2.0, BLACK);
            break;
        default:
            //DrawTexturePro(cammyidl, animation_frame(&ancammyidl, 5, 47, 84), (Rectangle){pos.x, pos.y, 47, 84}, (Vector2){0,0}, 0.0f, WHITE);
            break;
        }
        //DrawTexture(cammywlk, 10, 10, WHITE);
        
        
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
