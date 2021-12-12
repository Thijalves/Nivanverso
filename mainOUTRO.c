#include "raylib.h"
#include <stdio.h>
#include "player.h"

typedef enum {
    MENU = 0,
    PLAY,
    CREDITS,
} Selection;


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

    //variaveis do menu
    int framesCounter=0;
    Selection Option = MENU;

    //carerga os arquivos de mapa
    FILE *mapFile = fopen("../fase1.txt","r");
    if(mapFile == NULL)
        printf("erro ao abrir arquivo\n");
   
    const int screenWidth = 900;
    const int screenHeight = 544;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    //4 unidades eh o limite de pulo (pra quem joga bem)

    int mapWidth;

    fseek(mapFile, -11, SEEK_END);

    fscanf(mapFile, "width: %d", &mapWidth);

    printf("Largura do mapa: %d\n", mapWidth);

    EnvItem envItems[1000];

    fseek(mapFile, 0, SEEK_SET);

    Texture2D grassSingle = LoadTexture("../resources/tilemap/milinho.png");
    Texture2D GrassIntenalEdgeL = LoadTexture("../resources/tilemap/subidaE.png");
    Texture2D GrassIntenalEdgeD = LoadTexture("../resources/tilemap/subidaD.png");
    Texture2D grass = LoadTexture("../resources/tilemap/grama.png");
    Texture2D grassEdgeLeft = LoadTexture("../resources/tilemap/curvaE.png");
    Texture2D grassEdgeRight = LoadTexture("../resources/tilemap/curvaD.png");
    Texture2D grassWallLeft = LoadTexture("../resources/tilemap/gramaE.png");
    Texture2D grassWallRight = LoadTexture("../resources/tilemap/gramaD.png");
    Texture2D dirt = LoadTexture("../resources/tilemap/terra.png");
    Texture2D lava = LoadTexture("../resources/tilemap/lava.png");

    int posx = 0, posy = 0;
    for(int i = 0; i < 1000; i++){
        char block;

        fscanf(mapFile, "%c", &block);
        printf("%c", block);

        switch(block){
            case 'e':
                envItems[i].texture = grassEdgeLeft;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                break;
            break;
            case 'd':
                envItems[i].texture = grassEdgeRight;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                break;
            break;
            case 'l':
                envItems[i].texture = grassWallLeft;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                break;
            break;
            case 'r':
                envItems[i].texture = grassWallRight;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                break;
            break;
            case 'x':
                envItems[i].texture = dirt;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                break;
            case '^':
                envItems[i].texture = grass;
                envItems[i].color = GREEN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                break;
            case '@':
                envItems[i].texture = lava;
                envItems[i].color = RED;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
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

    //carrega a fonte
    Font font = LoadFontEx("../assets/font1.ttf", 50, 0, 0);
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

    //carrega o .txt
    char *text; text = NULL;
    text = LoadFileText("../data/about.txt");

    char *text2; text2 = NULL;
    text2 = LoadFileText("../data/credits.txt");

    char *text3; text3 = NULL;
    text3 = LoadFileText("../data/help.txt");

    //carrega os blocos
    Texture2D grama = LoadTexture("../resources/tilemap/grama.png");

    float timer = 0;
    int frame = 0;

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    SetTargetFPS(60);

    int help = 0;

    //detecta o que foi pressionado
    while (!WindowShouldClose() || help==1)    // Detect window close button or ESC key
    {
        help = 0;
        switch(Option){
            case MENU:
                if(IsKeyPressed(KEY_ENTER)){
                    Option = PLAY;
                } else if(IsKeyPressed(KEY_C)){
                    Option = CREDITS;
                }
                break;
        }

        switch(Option){

            case PLAY:
            {
                while (!WindowShouldClose()){

                    float deltaTime = GetFrameTime();

                    updateCamera(&camera, &player, screenWidth, screenHeight);

                    updatePlayer(&player, deltaTime, envItems, envItemsLength);

                    if(IsKeyPressed(KEY_R)){
                        player.position.y = 100;
                        player.position.x = 0;
                        player.vSpeed = 0;
                    }

                    BeginDrawing();
                    BeginMode2D(camera);

                    ClearBackground(BLUE);

                    for (int i = 0; i < envItemsLength; i++){
                        if(envItems[i].hasTexture)
                            DrawTextureV(envItems[i].texture, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, WHITE);
                        else
                            DrawRectangleRec(envItems[i].rect, envItems[i].color);
                    }
                    //for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //desenhna os obstaculos

                    //conta os frames para animacao
                    timer += GetFrameTime();
                    if(timer >= 0.075)
                    {
                        timer=0;
                        frame++;
                    }
                    frame = frame % player.idle.maxFrames;
                    player.frame.x = (player.frame.width *frame);

                    drawPlayer(&player); //desenha o player

                    EndMode2D();
                    EndDrawing();

                }
                
                UnloadTexture(grassSingle);
                UnloadTexture(GrassIntenalEdgeL);
                UnloadTexture(GrassIntenalEdgeD);
                UnloadTexture(grass);
                UnloadTexture(grassEdgeLeft);
                UnloadTexture(grassEdgeRight);
                UnloadTexture(grassWallLeft);
                UnloadTexture(grassWallRight);
                UnloadTexture(lava);
                UnloadTexture(GrassIntenalEdgeL);
                UnloadTexture(player.idle.texture);
                UnloadTexture(player.run.texture);
                UnloadTexture(player.runLeft.texture);
                UnloadTexture(player.falling.texture);
                UnloadTexture(player.jumping.texture);
                UnloadFont(font);
                UnloadFileText(text);
                UnloadFileText(text2);
                UnloadFileText(text3);
                CloseWindow();

            } break;

            case CREDITS:
            {
                if ("../data/credits.txt" != NULL)
                {
                    if (text2)
                    {
                        while(!WindowShouldClose()){
                            BeginDrawing();
                            ClearBackground(WHITE);
                            DrawText(text2, 190, 200, 20, BLUE);
                            DrawText("E - fechar\nESC - retornar", 400, 250, 20, BLACK);
                            EndDrawing();
                            if(IsKeyPressed(KEY_ESCAPE)){
                                Option = MENU;
                                help = 1;
                                break;
                            }
                        }
                    }
                }
            } break;

        }

        framesCounter+=3; //a cada frame, (x) letras sao printadas,  quanto maior, mais rapido
        BeginDrawing();
        
        ClearBackground(SKYBLUE);
        DrawTextEx(font, "NIVAN no Nivanverso", (Vector2){175, 100}, 35, 8, YELLOW);
        DrawTextEx(font, TextSubtext("INICIAR - Enter\n CREDITOS - C", 0, framesCounter/5), (Vector2){260, 225}, 35, 8, BLACK);
        
        EndDrawing();
    }
        
        UnloadTexture(grassSingle);
        UnloadTexture(GrassIntenalEdgeL);
        UnloadTexture(GrassIntenalEdgeD);
        UnloadTexture(grass);
        UnloadTexture(grassEdgeLeft);
        UnloadTexture(grassEdgeRight);
        UnloadTexture(grassWallLeft);
        UnloadTexture(grassWallRight);
        UnloadTexture(lava);
        UnloadTexture(GrassIntenalEdgeL);
        UnloadTexture(player.idle.texture);
        UnloadTexture(player.run.texture);
        UnloadTexture(player.runLeft.texture);
        UnloadTexture(player.falling.texture);
        UnloadTexture(player.jumping.texture);
        UnloadFont(font);
        UnloadFileText(text);
        UnloadFileText(text2);
        UnloadFileText(text3);
        CloseWindow();

    return 0;
}