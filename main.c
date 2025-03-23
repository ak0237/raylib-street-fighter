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
    enemy.type=0;
    enemy.animations = malloc((ANIMSTATESFINAL) * sizeof(Animation)); // Seta o ponteiro animations de cammy para um array dinamico de Animation (struct que contem os dados de posição, largura, frames, etc de cada animação) | ANIMSTATESFINAL é o último item de um enum que contem todas as animações, logo é alocado memória o suficiente para todas as animações
    enemy.textures = malloc((ANIMSTATESFINAL) * sizeof(Texture2D));
    handle_init_loads(&enemy);




    personagens cammy; // Cria uma personagem chamada cammy
    cammy.type = 1;
    cammy.animations = malloc((ANIMSTATESFINAL) * sizeof(Animation)); // Seta o ponteiro animations de cammy para um array dinamico de Animation (struct que contem os dados de posição, largura, frames, etc de cada animação) | ANIMSTATESFINAL é o último item de um enum que contem todas as animações, logo é alocado memória o suficiente para todas as animações
    cammy.textures = malloc((ANIMSTATESFINAL) * sizeof(Texture2D)); // Seta o ponteiro textures de cammy para um array dinâmico de Textures2D 
    handle_init_loads(&cammy); // Função handle_init_loads() recebe o endereço do personagem, e popula seus ponteiros animations e textures com dados pré definidos




    personagens entidades [] = {cammy, enemy};

    //===================================================================
    //===========================VARIÁVEIS INICIAIS DO PLAYER==================
    float speed = 100.0f; // Velocidade com que o player ira se mover
    Vector2 pos = {.x = 100, .y=100}; // Vetor que contem a posição do player
    Vector2 dir = {.x=0, .y=0}; // Vertor que contem a direção do player

    Vector2 epos = {150,100};
    Vector2 edir = {0,0};

    Vector2 positions [] = {pos, epos};
    Vector2 directions [] = {dir, edir};
    
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
    camera.target = (Vector2){ pos.x + 20.0f, pos.y + 20.0f }; // Seta o target da camera para a posição do player, com um deslocamento de 20.0 para centralizar melhot
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f; // Seta rotação da camera pa 0
    camera.zoom = 3.0f; // Seta zoom para 3

    Texture2D bg = LoadTexture("assets/personagens/bg.jpg");

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime(); // deltaTime 

        handleInput(directions, can_updates, animState); // Função que verifica se um input foi feito | Dependendo do input pode alterar a direção do player e/ou sua animação
        //handleInput(&edir, can_enemy_update_animation, &enemyAnimState, enemy.type);

        //====================================UPDATES=============================================
        animationupdate(entidades, can_updates, animState);
        //animationupdate(&cammy.animations[cammyanimState], &can_update_animation, &animState); // Seta onde os dados da animação de acordo com o animState

        //printf("%d\n", animState[PLAYER1]);
        
        pos.x += directions[PLAYER1].x * speed * dt; // Altera a posição em x de acordo com a direção do player | dt faz com que o movimento seja constante, não importando o fps
        pos.y += directions[PLAYER1].y * speed * dt; // Altera a posição em x de acordo com a direção do player 

        epos.x += directions[PLAYER2].x * speed * dt; // Altera a posição em x de acordo com a direção do player | dt faz com que o movimento seja constante, não importando o fps
        epos.y += directions[PLAYER2].y * speed * dt; // Altera a posição em x de acordo com a direção do player

        positions[PLAYER1] = pos;
        positions[PLAYER2] = epos;

        camera.target = (Vector2){ pos.x + 20, pos.y - 40 }; // Altera a posição da camera de acordo com a posição do player

        directions[PLAYER1] = (Vector2){0,0};
        directions[PLAYER2] = directions[PLAYER1];

        dir = (Vector2){.x=0, .y=0}; // Reseta a direção para (0,0) | player parado
        edir = dir;

        //printf("%d\n", entidades[PLAYER1].animations->cur);
       //=============================RENDERIZAÇÃO===================
        BeginDrawing(); // Inicia o ambiente de Drawing
        ClearBackground(SKYBLUE); // Apaga a tudo que está desenhado, e seta a cor do background para azul

        BeginMode2D(camera); // Inicia a camera 2d

        //DrawTexturePro(ota, (Rectangle){0,0,-47,84}, enemy, (Vector2){0,0}, 0.0f, WHITE); // Renderiza o inimigo

        DrawTexture(bg,0,0,WHITE);

        //printf("%d\n", animState[PLAYER2]);
        drawAnychar(&entidades[PLAYER2], &animState[PLAYER2], &positions[PLAYER2], PLAYER2);
        drawAnychar(&entidades[PLAYER1], &animState[PLAYER1], &positions[PLAYER1], PLAYER1); // Renderiza a animação do player

        //DrawCircle(pos.x, pos.y, 10.0, WHITE); // Desenha um circulo na origem do player | Debug

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

    CloseWindow(); // Fecha a janela

    int a;
    scanf("%d", &a);

    return 0;
}
