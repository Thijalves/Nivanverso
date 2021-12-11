#include "raylib.h"
#include <stdio.h>

#define gravity 350

typedef struct EnvItem {
    Rectangle rect;
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
    int playerState; // 0=idle 1=run 2 = jumping 3 = falling
    char facingDirection; //direita=1 esquerda=0
} Player;

//Funcao pra atualizar as variaveis do player
void updatePlayer(Player *player, float deltaTime, EnvItem *envItems, int envItemsLength){

    int hitFloor = 0;
    int hitWall = 0; // -1=esquerda e 1=direita
    
    //verifica as colisoes com cada obstaculo
    for (int i = 0; i < envItemsLength; i++){
        if (envItems[i].rect.x <= player->position.x + 15 &&
            envItems[i].rect.x + envItems[i].rect.width >= player->position.x &&
            envItems[i].rect.y >= player->position.y && 
            envItems[i].rect.y < player->position.y + player->vSpeed*deltaTime){
                hitFloor = 1;
                player->vSpeed = 0.0f;
                player->position.y = envItems[i].rect.y;
            }
        
        /* if(envItems[i].rect.width == 50){
            printf("Player: %f | plataforma: %f | subtracao: %f\n", player->position.x, envItems[i].rect.x, envItems[i].rect.x-(player->position.x+player->frame.width));
        }  */

        //detecta colosioes laterais
        if (envItems[i].rect.y < player->position.y && //se o topo do obstaculo esta acima do p
            (player->position.y-player->frame.height)<envItems[i].rect.y+envItems[i].rect.height && //se o pe do obstaculo esta acima do p
            player->position.x > envItems[i].rect.x && //se o obstaculo esta a esquerda do p
            player->position.x-(envItems[i].rect.x+envItems[i].rect.width) < 1){ // se a diferenca entre o x do p e do obstaculo e < 3
            hitWall = -1; 
            //printf(" Tem uma parede na esquerda ");
        }
        if (envItems[i].rect.y < player->position.y &&
            (player->position.y-player->frame.height)<envItems[i].rect.y+envItems[i].rect.height &&
            player->position.x < envItems[i].rect.x &&
            envItems[i].rect.x-(player->position.x+player->frame.width) < 1){
            hitWall = 1; 
                //printf("Tem uma parede na direita");
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
        player->playerState = 1;
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
        //deixar a velocidade de queda maior que a de subida
        if(player->vSpeed >=0){
            player->position.y += player->vSpeed*deltaTime;
            player->vSpeed += gravity*deltaTime;
        }else{
            player->position.y += player->vSpeed*deltaTime;
            player->vSpeed += gravity*deltaTime*1.4;
        }
        

        if(player->vSpeed < 0){ //player esta subindo
            player->playerState = 2;
            player->frame.width = (float)player->jumping.texture.width;
            player->frame.height = (float)player->jumping.texture.height;
        }else if(player->vSpeed > 10){
            player->playerState = 3;
            player->frame.width = (float)player->falling.texture.width;
            player->frame.height = (float)player->falling.texture.height;
        }

        player->canJump = false;
    }else{
        player->canJump = true;
    }

}

//Funcao para desenhar o player
void drawPlayer(Player *player){

    Rectangle invertedFrame = player->frame;
    Vector2 position = {player->position.x, player->position.y - 35}; //desenha o player com correcao de altura

    invertedFrame.width = -player->frame.width; //frame com comprimento invertido

    //anima de acordo com o estado
    switch(player->playerState){
        case 0: //boneco parado
            if(player->facingDirection)
                DrawTextureRec(player->idle.texture, player->frame,  position, WHITE);
            else
                DrawTextureRec(player->idle.texture, invertedFrame,  position, WHITE);

            break;
        case 1: //andando p direita
            if(player->facingDirection)
                DrawTextureRec(player->run.texture, player->frame, position, WHITE);
            else
                DrawTextureRec(player->run.texture, invertedFrame, position, WHITE);
            break;
        case 2: //pulando p direita
            if(player->facingDirection)
                DrawTextureRec(player->jumping.texture, player->frame, position, WHITE);
            else
                DrawTextureRec(player->jumping.texture, invertedFrame, position, WHITE);
            break;
        case 3: //caindo p direita
            if(player->facingDirection)
                DrawTextureRec(player->falling.texture, player->frame, position, WHITE);
            else
                DrawTextureRec(player->falling.texture, invertedFrame, position, WHITE);
            break;
    }
}

//Funcao para mover a camera (y fixo e x de acordo com o player)
void updateCamera(Camera2D *camera, Player *player, int screenWidth, int screenHeight){

    camera->offset = (Vector2){ (float)screenWidth/2, (float)screenHeight/2+6};

    float x, y;
    
    if(player->position.x <= 224){
        x = 225;
    }else if(player->position.x >= 3424){
        x = 3425;
    }else{
        x = player->position.x;
    }

    if(player->position.y <= 98){
        y = player->position.y-32;
    }else{
        y = (float)(screenHeight/2- 96);
    }

    camera->target = (Vector2){x, y};
    
    //(float)(screenHeight/2-48)
}

int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura

    FILE *mapFile = fopen("../fase.txt","r");

    if(mapFile == NULL)
        printf("erro ao abrir arquivo\n");
   
    const int screenWidth = 900;
    const int screenHeight = 544;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    // char chao[] = {1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,'\0'};
    //4 unidades eh o limite de pulo (pra quem joga bem)

    int mapWidth;

    fseek(mapFile, -11, SEEK_END);

    fscanf(mapFile, "width: %d", &mapWidth);

    printf("Largura do mapa: %d\n", mapWidth);


    EnvItem envItems[1000];

    fseek(mapFile, 0, SEEK_SET);

    int posx = 0, posy = 0;
    for(int i = 0; i < 1000; i++){
        char block;

        fscanf(mapFile, "%c", &block);
        printf("%c", block);

        switch(block){
            case 'x':
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                break;
            case '^':
                envItems[i].color = GREEN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                break;
            case '@':
                envItems[i].color = RED;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                break;
            default:
                break;
        }

        if(posx % 99*32 == 0 && posx != 0){
            posy += 32;
            posx = 0;
        } else {
            posx += 32;
        }
    }

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    //instancia o player com a animacao idle
    Player player = {0};
    player.hSpeed = 125;
    player.vSpeed = 0;
    player.jumpS = 250;
    player.idle.texture = LoadTexture("../resources/idle.png");
    player.idle.maxFrames = 12;
    player.position.x = 10;
    player.position.y = 256;
    player.frame.x = 0.0f;
    player.frame.y = 0.0f;
    player.facingDirection = 1;
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
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())   {
        float deltaTime = GetFrameTime();

        updateCamera(&camera, &player, screenWidth, screenHeight);

        updatePlayer(&player, deltaTime, envItems, envItemsLength);

        // printf("%f\n", player.position.x);

        if(IsKeyPressed(KEY_R)){
            player.position.y = 100;
            player.position.x = 0;
            player.vSpeed = 0;
        }
      
        BeginDrawing();
            BeginMode2D(camera);

                ClearBackground(BLUE);

                //for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //desenhna os obstaculos
                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //desenhna os obstaculos

                //conta os frames para animacao
                timer += GetFrameTime();
                if(timer >= 0.075){
                    timer=0;
                    frame++;
                }
                frame = frame % player.idle.maxFrames;
                player.frame.x = (player.frame.width *frame);

                drawPlayer(&player); //desenha o player

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