#include "raylib.h"

#define gravidade 400

typedef struct {
    Rectangle rect;
    int blocking;
    Color color;
} Chao;

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
    float hSpeed;
    float vSpeed;
} Player;

void updatePlayer(Player *player, float deltaTime, int *estado){

    //atualiza o estado de animacao e o movimento horizonal
    if(IsKeyDown(KEY_D)){
            player->position.x += player->hSpeed*deltaTime;
            *estado = 1;
            player->frame.width = (float)player->run.texture.width/player->run.maxFrames;
            player->frame.height = (float)player->run.texture.height;
    }else if(IsKeyDown(KEY_A)){
        player->position.x -= player->hSpeed*deltaTime;
        *estado = 1;
        player->frame.width = -(float)player->run.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->run.texture.height;
    }else{
        *estado = 0;
        player->frame.width = (float)player->idle.texture.width/player->idle.maxFrames;
        player->frame.height = (float)player->idle.texture.height;
    }

    int hitObstacle = 0;

    /* player->position.y += player->vSpeed*deltaTime;
    player->vSpeed += gravidade*deltaTime;  */


}


int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    //inicializa o chao
    Chao chao = {0};
    chao.rect.x = 300;
    chao.rect.y = 260;
    chao.rect.width = 200;
    chao.rect.height = 5;
    chao.color = GREEN;
    //sombra
    Chao sombra = {0};
    sombra.rect.x = 302;
    sombra.rect.y = 262;
    sombra.rect.width = 200;
    sombra.rect.height = 5;
    sombra.color = DARKGRAY;

    //instancia o player com a animacao idle
    Player player = {0};
    player.hSpeed = 125;
    player.vSpeed = 0;
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

        updatePlayer( &player, deltaTime, &playerState);

        if(IsKeyPressed(KEY_R)){
            player.position.y = 0;
            player.vSpeed = 0;
        }
      
        BeginDrawing();
            BeginMode2D(camera);

            ClearBackground(BLUE);
            
            DrawRectangleRec(sombra.rect, sombra.color);
            DrawRectangleRec(chao.rect, chao.color);

            timer += GetFrameTime();
            if(timer >= 0.075){
                timer=0;
                frame++;
            }

            frame = frame % player.idle.maxFrames;
            player.frame.x = (player.frame.width *frame);

            if(playerState){
                DrawTextureRec(player.run.texture, player.frame, player.position, WHITE);
            }else{
                DrawTextureRec(player.idle.texture, player.frame, player.position, WHITE);
            }

            EndMode2D();
        EndDrawing();

    }

    UnloadTexture(player.idle.texture);
    UnloadTexture(player.run.texture);

    CloseWindow();                

    return 0;
}