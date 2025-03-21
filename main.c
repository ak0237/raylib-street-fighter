#include "include/raylib.h"
#include "include/animator.h"
#include "include/handleinput.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   // Configurações iniciais
    const int screenWidth = 800; // Largura da tela
    const int screenHeight = 450; // Altura da Tela
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window"); // Cria a janela onde o game será rodado
    SetTargetFPS(60);   // Seta fps

    //=============================================
    //==================== LOADS INICIAIS DO GAME============================
    
    Texture2D ota = LoadTexture("assets/personagens/ota.png"); // Carrega o sprite ca dammy rosa | usando apenas para testes
    personagens cammy; // Cria uma personagem chamada cammy
    cammy.animations = malloc((ANIMSTATESFINAL) * sizeof(Animation)); // Seta o ponteiro animations de cammy para um array dinamico de Animation (struct que contem os dados de posição, largura, frames, etc de cada animação) | ANIMSTATESFINAL é o último item de um enum que contem todas as animações, logo é alocado memória o suficiente para todas as animações
    cammy.textures = malloc((ANIMSTATESFINAL) * sizeof(Texture2D)); // Seta o ponteiro textures de cammy para um array dinâmico de Textures2D 
    handle_init_loads(&cammy); // Função handle_init_loads() recebe o endereço do personagem, e popula seus ponteiros animations e textures com dados pré definidos

    //===================================================================
    //===========================VARIÁVEIS INICIAIS DO PLAYER==================
    float speed = 100.0f; // Velocidade com que o player ira se mover
    Vector2 pos = {.x = 10, .y=10}; // Vetor que contem a posição do player
    Vector2 dir = {.x=0, .y=0}; // Vertor que contem a direção do player
    
    //======================================================================
    //==========================VARIÁVEIS INICIAIS DO INIMIGO===============
    Rectangle enemy = {120, 150, 47, 84}; // Retangulo com a posição de onde o inimigo será spawnado
    //======================================================================
    //=========================VARIÁVEIS DO JOGO=======================    
    enum animStates animState;  // Cria uma variável enum animStates chamada animState | animStates é um enum que contém todas as animações
    bool can_update_animation = true; // Bolleano usado para permitir que as animações ocorram | animações do tipo ONESHOT (pulo, soco, chute, etc) são executadas apenas uma vez quando o botão correspondente é pressionado, e não podem ser interrompidas, logo esse bolleano se torna falso quando esse tipo de animação começa a ser executado, e verdadeiro quando a animação acaba
    animState = IDLE; // Define o animState antes de começar o jogo como IDLE, logo o personagem começara estando em animação de idle
    
    //========================================================================
    //==================COFIGURAÇÃO DA CAMERA=============================
    Camera2D camera; //Cira uma camera 2d
    camera.target = (Vector2){ pos.x + 20.0f, pos.y + 20.0f }; // Seta o target da camera para a posição do player, com um deslocamento de 20.0 para centralizar melhot
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f; // Seta rotação da camera pa 0
    camera.zoom = 4.0f; // Seta zoom para 4

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime(); // deltaTime 

        handleInput(&dir, can_update_animation, &animState); // Função que verifica se um input foi feito | Dependendo do input pode alterar a direção do player e/ou sua animação


        //====================================UPDATES=============================================
        animationupdate(&cammy.animations[animState], &can_update_animation, &animState); // Seta onde os dados da animação de acordo com o animState
        
        pos.x += dir.x * speed * dt; // Altera a posição em x de acordo com a direção do player | dt faz com que o movimento seja constante, não importando o fps
        pos.y += dir.y * speed * dt; // Altera a posição em x de acordo com a direção do player 

        camera.target = (Vector2){ pos.x + 20, pos.y - 40 }; // Altera a posição da camera de acordo com a posição do player

        dir = (Vector2){.x=0, .y=0}; // Reseta a direção para (0,0) | player parado

       
       //=============================RENDERIZAÇÃO===================
        BeginDrawing(); // Inicia o ambiente de Drawing
        ClearBackground(SKYBLUE); // Apaga a tudo que está desenhado, e seta a cor do background para azul

        BeginMode2D(camera); // Inicia a camera 2d

        DrawTexturePro(ota, (Rectangle){0,0,-47,84}, enemy, (Vector2){0,0}, 0.0f, WHITE); // Renderiza o inimigo


        drawAnychar(&cammy, animState, pos); // Renderiza a animação do player

        DrawCircle(pos.x, pos.y, 10.0, WHITE); // Desenha um circulo na origem do player | Debug

        EndMode2D(); // Enderra a camera 

        EndDrawing(); // Encerra o ambiente de renderização
   
    }
    //=======================================LIBERANDO A MEMÓRIA =============================================
    for (int i = 0; i < ANIMSTATESFINAL; i++) { // Descarrega as texturas do player
        UnloadTexture(cammy.textures[i]);
    }
    UnloadTexture(ota); // Descarrega a textura do inimigo
    free(cammy.animations); // Libera o espaço alocado para os dados das animações
    free(cammy.textures); // Libera o espaço alocado para as texturas 

    CloseWindow(); // Fecha a janela


    return 0;
}
