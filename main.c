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
    Sprite jumping;
    Sprite falling;
    float jumpS;
    float hSpeed;
    float vSpeed;
    char canJump;
    int playerState; // 0=idle 1=run 2 = runL
    char facingDirection; //direita=1 esquerda=0
} Player;

//Funcao pra atualizar as variaveis do player
void updatePlayer(Player *player, float deltaTime, EnvItem *envItems, int envItemsLength){


    int hitFloor = 0;
    int hitWall = 0; // -1=esquerda e 1=direita
    
    //verifica as colisoes com cada obstaculo
    for (int i = 0; i < envItemsLength; i++){
        if (envItems[i].blocking && envItems[i].rect.x <= player->position.x + 15 &&
            envItems[i].rect.x + envItems[i].rect.width >= player->position.x &&
            envItems[i].rect.y >= player->position.y && 
            envItems[i].rect.y < player->position.y + player->vSpeed*deltaTime){
                hitFloor = 1;
                player->vSpeed = 0.0f;
                player->position.y = envItems[i].rect.y;
            }
        
        if(envItems[i].rect.width == 50){
            printf("Player: %f | plataforma: %f | subtracao: %f\n", player->position.x, envItems[i].rect.x, player->position.x-(envItems[i].rect.x+envItems[i].rect.width));
        } 

        //detecta colosioes laterais
        if (envItems[i].rect.y < player->position.y && //se o topo do obstaculo esta acima do p
            (player->position.y-player->frame.height)<envItems[i].rect.y+envItems[i].rect.height && //se o pe do obstaculo esta acima do p
            player->position.x > envItems[i].rect.x && //se o ostaculo esta a esquerda do p
            player->position.x-(envItems[i].rect.x+envItems[i].rect.width) < 3){ // se a diferenca entre o x do p e do obstaculo e < 3
            hitWall = -1; 
            printf(" Tem uma parede na esquerda ");
        }
        if (envItems[i].rect.y < player->position.y && 
            player->position.x + 21 - envItems[i].rect.x > -2 &&
            player->position.x < envItems[i].rect.x){
            hitWall = 1; 
            //printf("Tem uma parede na direita\n");
        }
    
    }

    //atualiza o estado de animacao e o movimento horizonal
    if(IsKeyDown(KEY_D) && hitWall != 1){
        player->facingDirection = 1;
        player->position.x += player->hSpeed*deltaTime;
        player->playerState = 1;
        player->frame.width = (float)player->run.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->run.texture.height;
    }else if(IsKeyDown(KEY_A) && hitWall != -1){
        player->facingDirection = 0;
        player->position.x -= player->hSpeed*deltaTime;
        player->playerState = 2;
        player->frame.width = (float)player->runLeft.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->runLeft.texture.height;
    }else{
        player->playerState = 0;
        player->frame.width = (float)player->idle.texture.width/player->idle.maxFrames;
        player->frame.height = (float)player->idle.texture.height;
    }

    //detecta pulo
    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->vSpeed = -player->jumpS;
        player->canJump = false;
    }

    if (!hitFloor){
        player->position.y += player->vSpeed*deltaTime;
        player->vSpeed += gravity*deltaTime;

        if(player->vSpeed < 0){ //player esta subindo

            if(IsKeyDown(KEY_A)){
                player->playerState = 4;
            }else{
                player->playerState = 3;
            }
            player->frame.width = (float)player->jumping.texture.width;
            player->frame.height = (float)player->jumping.texture.height;

        }else if(player->vSpeed > 10){

            if(IsKeyDown(KEY_A)){
                player->playerState = 6;
            }else {
                player->playerState = 5;
            }
            player->frame.width = (float)player->falling.texture.width;
            player->frame.height = (float)player->falling.texture.height;
            printf("estou caindoo\n");
        }

        player->canJump = false;
    }else{
        player->canJump = true;
    }

}

void drawPlayer(Player *player){
    Rectangle frame = player->frame;
    Vector2 position = {player->position.x, player->position.y - 35}; //desenha o player com correcao de altura

    if(player->playerState == 4 || player->playerState == 6)
        frame.width = -player->frame.width;

    //anima de acordo com o estado
    switch(player->playerState){
        case 0: //boneco parado
            DrawTextureRec(player->idle.texture, player->frame,  position, WHITE);
            break;
        case 1: //andando p direita
            DrawTextureRec(player->run.texture, player->frame, position, WHITE);
            break;
        case 2: //andando p esquerda
            DrawTextureRec(player->runLeft.texture, player->frame, position, WHITE);
            break;
        case 3: //pulando p direita
            DrawTextureRec(player->jumping.texture, player->frame, position, WHITE);
            break;
        case 4: //pulando p esquerda
            DrawTextureRec(player->jumping.texture, frame, position, WHITE);
            break;
        case 5: //caindo p direita
            DrawTextureRec(player->falling.texture, player->frame, position, WHITE);
            break;
        case 6: //caindo p direita
            DrawTextureRec(player->falling.texture, frame, position, WHITE);
            break;
    }
}


int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    EnvItem envItems[] = {
        {{ 150, 300, 200, 100}, 1, GREEN },
        {{ 240, 250, 50, 50 }, 1, GREEN },
        {{ 430, 250, 100, 10 }, 1, GREEN },
        {{ 420, 150, 10, 50 }, 1, GREEN}
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

    //animacao de correr para a esquerda
    player.runLeft.texture = LoadTexture("../resources/runLeft.png");
    player.runLeft.maxFrames = 8;

    //sprite pulando
    player.jumping.texture = LoadTexture("../resources/jumping.png");
    player.jumping.maxFrames = 1;

    //sprite caindo
    player.falling.texture = LoadTexture("../resources/falling.png");
    player.falling.maxFrames = 1;

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


        updatePlayer(&player, deltaTime, envItems, envItemsLength);

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

                drawPlayer(&player);

            EndMode2D();
        EndDrawing();

    }

    UnloadTexture(player.idle.texture);
    UnloadTexture(player.run.texture);
    UnloadTexture(player.runLeft.texture);
    UnloadTexture(player.falling.texture);
    UnloadTexture(player.jumping.texture);

    CloseWindow();                

    return 0;
}