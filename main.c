#include "raylib.h"
#include <stdio.h>

#define gravity 400

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

typedef struct {
    Texture2D texture;
    int width;
    int height;
    int maxFrames;
} Sprite;

typedef struct {
    Rectangle frame;
    Vector2 position;
    Sprite idle;
    Sprite run;
    Sprite runLeft;
    float jumpS;
    float hSpeed;
    float vSpeed;
    char canJump;
} Player;

//Funcao pra atualizar as variaveis do player
void updatePlayer(Player *player, float deltaTime, int *playerState, EnvItem *envItems, int envItemsLength){

    //atualiza o estado de animacao e o movimento horizonal
    if(IsKeyDown(KEY_D)){
        player->position.x += player->hSpeed*deltaTime;
        *playerState = 1;
        player->frame.width = (float)player->run.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->run.texture.height;
    }else if(IsKeyDown(KEY_A)){
        player->position.x -= player->hSpeed*deltaTime;
        *playerState = 2;
        player->frame.width = (float)player->runLeft.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->runLeft.texture.height;
    }else{
        *playerState = 0;
        player->frame.width = (float)player->idle.texture.width/player->idle.maxFrames;
        player->frame.height = (float)player->idle.texture.height;
    }

    //detecta pulo
    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->vSpeed = -player->jumpS;
        player->canJump = false;
    }

    int hitObstacle = 0;
    
    //verifica as colisoes com cada obstaculo
    for (int i = 0; i < envItemsLength; i++){
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking && ei->rect.x <= p->x + 15 &&
            ei->rect.x + ei->rect.width >= p->x - 15 &&
            ei->rect.y >= p->y && ei->rect.y < p->y + player->vSpeed*deltaTime){
                hitObstacle = 1;
                player->vSpeed = 0.0f;
                p->y = ei->rect.y;
        }
    }

    if (!hitObstacle){
        player->position.y += player->vSpeed*deltaTime;
        player->vSpeed += gravity*deltaTime;
        player->canJump = false;
    }else 
        player->canJump = true;

}


int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    EnvItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, BLUE },
        {{ 251, 301, 100, 10 }, 0, DARKGRAY},
        {{ 250, 300, 100, 10 }, 1, GREEN },
        {{ 401, 301, 100, 10 }, 0, DARKGRAY},
        {{ 400, 300, 100, 10 }, 1, GREEN }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    //instancia o player com a animacao idle
    Player player = {0};
    player.hSpeed = 125;
    player.vSpeed = 0;
    player.jumpS = 250;
    player.idle.texture = LoadTexture("../resources/idle.png");
    player.idle.maxFrames = 12;
    player.position.x = screenWidth/2;
    player.position.y = screenHeight/2;
    player.frame.x = 0.0f;
    player.frame.y = 0.0f;
    player.frame.width = (float)player.idle.texture.width/player.idle.maxFrames;
    player.frame.height = (float)player.idle.texture.height;

    //carrega a anumacao run
    player.run.texture = LoadTexture("../resources/run.png");
    player.run.maxFrames = 8;

    //animcao de correr para a esquerda
    player.runLeft.texture = LoadTexture("../resources/runLeft.png");
    player.run.maxFrames = 8;

    float timer = 0;
    int frame = 0;

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())   {

        float deltaTime = GetFrameTime();

        int playerState = 0; // 0=idle 1=run 2 = runL

        updatePlayer( &player, deltaTime, &playerState, envItems, envItemsLength);

        if(IsKeyPressed(KEY_R)){
            player.position.y = 0;
            player.vSpeed = 0;
        }
      
        BeginDrawing();
            BeginMode2D(camera);

                ClearBackground(BLUE);

                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //cria os obstaculos

                //conta os frames para animacao
                timer += GetFrameTime();
                if(timer >= 0.075){
                    timer=0;
                    frame++;
                }
                frame = frame % player.idle.maxFrames;
                player.frame.x = (player.frame.width *frame);

                Vector2 position = {player.position.x, player.position.y - 35}; //desenha o player com correcao de altura

                //anima de acordo com o estado
                switch(playerState){
                    case 0: //boneco parado
                        DrawTextureRec(player.idle.texture, player.frame,  position, WHITE);
                        break;
                    case 1: //andando p direita
                        DrawTextureRec(player.run.texture, player.frame, position, WHITE);
                        break;
                    case 2: //andando p esquerda
                        DrawTextureRec(player.runLeft.texture, player.frame, position, WHITE);
                        break;
                }

            EndMode2D();
        EndDrawing();

    }

    UnloadTexture(player.idle.texture);
    UnloadTexture(player.run.texture);

    CloseWindow();                

    return 0;
}