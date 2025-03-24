#include "include/raylib.h"
#include "include/animator.h"
#include "include/handleinput.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   // Configurações iniciais
    const int screenWidth = 960; // Largura da tela
    const int screenHeight = 561; // Altura da Tela
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); // Cria a janela onde o game será rodado
    SetTargetFPS(60);   // Seta fps

    //=============================================
    //==================== LOADS INICIAIS DO GAME============================
    
    //Texture2D ota = LoadTexture("assets/personagens/ota.png"); // Carrega o sprite ca dammy rosa | usando apenas para testes
    personagens enemy;
    enemy.animationState = IDLE;
    enemy.animationSubState = IDLING;
    enemy.velocity = (Vector2){100.0f, 0.0f};
    enemy.type=0;
    enemy.animations = malloc((ANIMSTATESFINAL) * sizeof(Animation)); // Seta o ponteiro animations de cammy para um array dinamico de Animation (struct que contem os dados de posição, largura, frames, etc de cada animação) | ANIMSTATESFINAL é o último item de um enum que contem todas as animações, logo é alocado memória o suficiente para todas as animações
    enemy.textures = malloc((ANIMSTATESFINAL) * sizeof(Texture2D));
    handle_init_loads(&enemy);




    personagens cammy; // Cria uma personagem chamada cammy
    cammy.animationState = IDLE;
    cammy.animationSubState = IDLING;
    cammy.velocity = (Vector2){100.0f, 0.0f};
    cammy.type = 1;
    cammy.animations = malloc((ANIMSTATESFINAL) * sizeof(Animation)); // Seta o ponteiro animations de cammy para um array dinamico de Animation (struct que contem os dados de posição, largura, frames, etc de cada animação) | ANIMSTATESFINAL é o último item de um enum que contem todas as animações, logo é alocado memória o suficiente para todas as animações
    cammy.textures = malloc((ANIMSTATESFINAL) * sizeof(Texture2D)); // Seta o ponteiro textures de cammy para um array dinâmico de Textures2D 
    handle_init_loads(&cammy); // Função handle_init_loads() recebe o endereço do personagem, e popula seus ponteiros animations e textures com dados pré definidos

    cammy.retangulos = malloc (ANIMSTATESFINAL* 10 * sizeof(Rectangle));
    cammy.position = (Vector2){.x = 180, .y=220}; // Vetor que contem a posição do player
    cammy.direction = (Vector2){.x=0, .y=0};
    cammy.pushbox = (Rectangle){.x=cammy.position.x, .y=cammy.position.y-90, .width = 50, .height=90};


    enemy.position = (Vector2){204,220};
    enemy.direction = (Vector2){0,0};
    enemy.pushbox = (Rectangle){.x=enemy.position.x, .y=enemy.position.y, .width = 20, .height=90};

    personagens entidades [] = {cammy, enemy};

    //===================================================================
    //===========================VARIÁVEIS INICIAIS DO PLAYER==================
    float speed = 100.0f; // Velocidade com que o player ira se mover
    //float jmpspd = -500.0f;
     // Vertor que contem a direção do player


    
    //======================================================================
    //==========================VARIÁVEIS INICIAIS DO INIMIGO===============
    //Rectangle enemy = {120, 150, 47, 84}; // Retangulo com a posição de onde o inimigo será spawnado
    //======================================================================
    //=========================VARIÁVEIS DO JOGO=======================    
    enum animStates cammyanimState;  // Cria uma variável enum animStates chamada animState | animStates é um enum que contém todas as animações
    bool can_update_animation = true; // Bolleano usado para permitir que as animações ocorram | animações do tipo ONESHOT (pulo, soco, chute, etc) são executadas apenas uma vez quando o botão correspondente é pressionado, e não podem ser interrompidas, logo esse bolleano se torna falso quando esse tipo de animação começa a ser executado, e verdadeiro quando a animação acaba
    cammyanimState = IDLE; // Define o animState antes de começar o jogo como IDLE, logo o personagem começara estando em animação de idle

    enum animStates enemyAnimState = IDLE;
    bool can_enemy_update_animation = true;

    bool can_updates[] ={can_update_animation, can_enemy_update_animation};
    enum animStates animState [] = {cammyanimState, enemyAnimState};

    
    //========================================================================
    //==================COFIGURAÇÃO DA CAMERA=============================
    Camera2D camera; //Cira uma camera 2d
    camera.target = (Vector2){  20.0f, 00.0f }; // Seta o target da camera para a posição do player, com um deslocamento de 20.0 para centralizar melhot
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f; // Seta rotação da camera pa 0
    camera.zoom = 3.0f; // Seta zoom para 3

    Texture2D bg = LoadTexture("assets/personagens/bg.png");

    int firstDraw, secondDraw;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime(); // deltaTime 

        handleInput(can_updates, animState, entidades);

        //handleInput(directions, can_updates, animState, ); // Função que verifica se um input foi feito | Dependendo do input pode alterar a direção do player e/ou sua animação
        //handleInput(&edir, can_enemy_update_animation, &enemyAnimState, enemy.type);

        //====================================UPDATES=============================================
        //printf("%d\n", entidades[PLAYER1].animationSubState);
        animationupdate(entidades, can_updates, animState);
        //animationupdate(&cammy.animations[cammyanimState], &can_update_animation, &animState); // Seta onde os dados da animação de acordo com o animState

        //printf("%d\n", animState[PLAYER1]);

        //if(entidades[PLAYER1].animationState != JUMP) entidades[PLAYER1].direction.y =-1; 
        
        //pos.x += entidades[PLAYER1].direction.x  * speed * dt; // Altera a posição em x de acordo com a direção do player | dt faz com que o movimento seja constante, não importando o fps
        //entidades[PLAYER1].velocity.y += 20.0f;
       // entidades[PLAYER1].position.y += entidades[PLAYER1].velocity.y * dt;
        // pos.y += entidades[PLAYER1].direction.y  jmpspd * dt; // Altera a posição em x de acordo com a direção do player 

        //epos.x += entidades[PLAYER2].direction.x * speed * dt; // Altera a posição em x de acordo com a direção do player | dt faz com que o movimento seja constante, não importando o fps
        //epos.y -= entidades[PLAYER2].direction.y * jmpspd * dt; // Altera a posição em x de acordo com a direção do player

        entidades[PLAYER2].facing  = (entidades[PLAYER1].position.x - entidades[PLAYER2].position.x > 0) ? 1 : -1;
        entidades[PLAYER1].facing  = (entidades[PLAYER2].position.x - entidades[PLAYER1].position.x > 0) ? 1 : -1;

        //entidades[PLAYER1].position.x - entidades[PLAYER2].position.x > 0 ? entidades[PLAYER2].facing = 1 : entidades[PLAYER2].facing = -1;
       // printf("%f %d\n", entidades[PLAYER1].direction.x, entidades[PLAYER1].facing);
        //if(IsKeyDown(KEY_W) && entidades[PLAYER1].direction.x == entidades[PLAYER1].facing) printf("foi\n"); 
        for(int i = PLAYER1; i <= PLAYER2; i++){
            entidades[i].position.x += entidades[i].direction.x  * entidades[i].velocity.x * dt;
            if(CheckCollisionRecs(entidades[PLAYER1].pushbox, entidades[PLAYER2].pushbox) && entidades[i].direction.x == entidades[i].facing){ 
                //entidades[i].direction.x = 0;
                switch (i)
                {
                case PLAYER1:
                    entidades[PLAYER2].position.x += entidades[PLAYER1].direction.x  * entidades[PLAYER1].velocity.x * dt;
                    break;
                case PLAYER2:
                    entidades[PLAYER1].position.x += entidades[PLAYER2].direction.x  * speed * dt;
                    break;
                default:
                    break;
                }
            }
            entidades[i].velocity.y += 20.0f;
            entidades[i].position.y += entidades[i].velocity.y * dt;
            if(entidades[i].position.y > 220.0f){ 
                entidades[i].position.y = 220.0f;
                entidades[i].velocity.y = 0;
                entidades[i].grounded = true;\
            }
            if(entidades[i].grounded) entidades[i].direction.x = 0;

            entidades[i].pushbox = (Rectangle){.x = entidades[i].position.x-20, .y=entidades[i].position.y-90, .width = 25, .height = 90};
        }
        

        
        //dir = (Vector2){.x=0}; // Reseta a direção para (0,0) | player parado
        //edir = dir;
        

      
        
        camera.target = (Vector2){ entidades[PLAYER1].position.x + 20, 220 - 80 }; // Altera a posição da camera de acordo com a posição do player
        
        //printf("%d\n", entidades[PLAYER1].animations->cur);
       //=============================RENDERIZAÇÃO===================
        BeginDrawing(); // Inicia o ambiente de Drawing
        ClearBackground(SKYBLUE); // Apaga a tudo que está desenhado, e seta a cor do background para azul

        BeginMode2D(camera); // Inicia a camera 2d

        //DrawTexturePro(ota, (Rectangle){0,0,-47,84}, enemy, (Vector2){0,0}, 0.0f, WHITE); // Renderiza o inimigo

        DrawTexture(bg,0,0,WHITE);

        //printf("%d\n", animState[PLAYER2]);

        

        if(entidades[PLAYER1].layer >= entidades[PLAYER2].layer){
            firstDraw = PLAYER2;
            secondDraw = PLAYER1;
        }else{
            firstDraw = PLAYER1;
            secondDraw = PLAYER2;
        }
          
        drawAnychar(&entidades[firstDraw], &animState[firstDraw]);
        drawAnychar(&entidades[secondDraw], &animState[secondDraw]); // Renderiza a animação do player

        //DrawRectangleLinesEx(entidades[PLAYER1].pushbox, 2.0f, RED);
        //printf("x = %f | y = %f | w = %f | h = %f \n", entidades[PLAYER1].pushbox.x, entidades[PLAYER1].pushbox.y, entidades[PLAYER1].pushbox.width, entidades[PLAYER1].pushbox.height);

        //DrawRectangleRec(entidades[PLAYER1].pushbox, GREEN);

        //DrawCircle(entidades[PLAYER1].position.x, entidades[PLAYER1].position.y, 10.0, WHITE); // Desenha um circulo na origem do player | Debug

        EndMode2D(); // Enderra a camera 

        EndDrawing(); // Encerra o ambiente de renderização
   
    }
    //=======================================LIBERANDO A MEMÓRIA =============================================
    for (int i = 0; i < ANIMSTATESFINAL; i++) { // Descarrega as texturas do player
        UnloadTexture(cammy.textures[i]);
        UnloadTexture(enemy.textures[i]);
    }
    UnloadTexture(bg);
    //UnloadTexture(ota); // Descarrega a textura do inimigo
    free(cammy.animations); // Libera o espaço alocado para os dados das animações
    free(cammy.textures); // Libera o espaço alocado para as texturas 
    free(enemy.animations);
    free(enemy.textures);
    free(cammy.retangulos);

    CloseWindow(); // Fecha a janela

    //int a;
    //scanf("%d", &a);

    return 0;
}
