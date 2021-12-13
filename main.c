#include "raylib.h"
#include <stdio.h>
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "updatePlayer.h"
#include "drawPlayer.h"
#include "updateCamera.h"
#include "initiatePlayer.h"
#include "initiateCamera.h"
#include "mapGenerator.h"

typedef enum {
    MENU = 0,
    PLAY,
    CREDITS,
} Selection;

typedef struct {
    Rectangle rectangle;
    Texture2D texture;
    int speed;
    char type;
    Vector2 initialPosition;
    char direction; //-1 esquerda | 1 direita
    Color color;
} Enemy;


int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura
    
    float peaoTimer = 0;
    float lavaTimer = 0;
    int lavaFrame = 0;
    
    //variaveis do menu
    int framesCounter=0;
    Selection Option = MENU;

    generateMap();
    //carerga os arquivos de mapa
    FILE *mapFile = fopen("./data/fase1.txt","r");
    if(mapFile == NULL)
        printf("erro ao abrir arquivo\n");
    const int screenWidth = 900;
    const int screenHeight = 544;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    int mapWidth;

    fseek(mapFile, -11, SEEK_END);

    fscanf(mapFile, "width: %d", &mapWidth);

    printf("Largura do mapa: %d\n", mapWidth);

    EnvItem envItems[1000];

    fseek(mapFile, 0, SEEK_SET);

    Texture2D sky = LoadTexture("./textures/ceu.png");
    Texture2D grassSingle = LoadTexture("./tilemap/miolinho.png");
    Texture2D GrassIntenalEdgeL = LoadTexture("./textures/tilemap/subidaE.png");
    Texture2D GrassIntenalEdgeD = LoadTexture("./textures/tilemap/subidaD.png");
    Texture2D grass = LoadTexture("./textures/tilemap/grama.png");
    Texture2D grassEdgeLeft = LoadTexture("./textures/tilemap/curvaE.png");
    Texture2D grassEdgeRight = LoadTexture("./textures/tilemap/curvaD.png");
    Texture2D grassWallLeft = LoadTexture("./textures/tilemap/gramaE.png");
    Texture2D grassWallRight = LoadTexture("./textures/tilemap/gramaD.png");
    Texture2D dirt = LoadTexture("./textures/tilemap/terra.png");
    Texture2D lava =  LoadTexture("./textures/tilemap/lava.png");

    
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
                envItems[i].isLava = 0;
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
                envItems[i].isLava = 0;
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
                envItems[i].isLava = 0;
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
                envItems[i].isLava = 0;
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
                envItems[i].isLava = 0;
                break;
            case '^':
                envItems[i].texture = grass;
                envItems[i].color = GREEN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                envItems[i].isLava = 0;
                break;
            case '@':
                envItems[i].texture = lava;
                envItems[i].color = RED;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture =1;
                envItems[i].isLava = 1;
                envItems[i].frame.x = 0.0f;
                envItems[i].frame.y = 0.0f;
                envItems[i].frame.width = 32;
                envItems[i].frame.height = 32;
                break;
            default:
                envItems[i].hasTexture = 0;
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
    initiatePlayer(&player);

    Enemy peao = {0};
    peao.texture = LoadTexture("./textures/inimigo/peao.png");
    peao.rectangle.x = player.position.x + 64;
    peao.initialPosition.x = player.position.x + 256;
    peao.rectangle.y = player.position.y - 40;
    peao.initialPosition.y = peao.rectangle.y;
    peao.rectangle.width = 20;
    peao.rectangle.height = 40;
    peao.direction = 1;
    peao.speed = 50;
    peao.color = ORANGE;

    //carrega a fonte
    Font font = LoadFontEx("./assets/font1.ttf", 50, 0, 0);
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

    //carrega o .txt
    char *text; text = NULL;
    text = LoadFileText("./data/about.txt");

    char *text2; text2 = NULL;
    text2 = LoadFileText("./data/credits.txt");


    float playerTimer = 0;
    int playerFrame = 0;

    Camera2D camera = { 0 };
    initiateCamera(&camera, player, screenWidth, screenHeight);

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
            case PLAY:
                break;
            case CREDITS:
                break;
        }

        switch(Option){

            //pega a posicao inicial + um valor e - esse valor
            //incrementar a pos x até a soma e subtarir x até a subtracao

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
                    
                    peaoTimer += GetFrameTime();
                    //Desenha o inimigo
                    if( peaoTimer >= 0.02){
                        peaoTimer = 0;
                        if(peao.rectangle.x >= peao.initialPosition.x + 96){
                            peao.direction = -1;
                        }else if(peao.rectangle.x <= peao.initialPosition.x - 96){
                            peao.direction = 1;
                        }
                        peao.rectangle.x += peao.direction*peao.speed*deltaTime;
                    }
                    //detecta colisoes
                    //printf("%f %f\n", player.position.x+32, peao.rectangle.x);
                     if( player.position.x + player.frame.width >= peao.rectangle.x && 
                        player.position.x <= peao.rectangle.x + peao.rectangle.width && 
                        player.position.y >= peao.rectangle.y){
                        
                        if(player.position.y - peao.rectangle.y < 5){
                            printf("matei o peao\n");
                            player.vSpeed = -player.jumpS;
                        }else{
                            player.color = GRAY;
                            player.vSpeed = -player.jumpS/2;
                            printf("mori\n");
                        }

                    } 

                    //conta os frames para animacao
                    playerTimer += GetFrameTime();
                    if(playerTimer >= 0.075f){
                        playerTimer=0;
                        playerFrame++;
                    }
                    playerFrame = playerFrame % player.idle.maxFrames;
                    player.frame.x = (player.frame.width*playerFrame);
                    
                    DrawTextureV(sky, (Vector2){0,0}, WHITE);

                    //DrawRectangleRec(peao.rectangle, peao.color);
                    DrawTextureV(peao.texture, (Vector2) {peao.rectangle.x,peao.rectangle.y}, WHITE);

                    //for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //desenhna os obstaculos
                    for (int i = 0; i < envItemsLength; i++){
                        if(envItems[i].hasTexture){
                            if(envItems[i].isLava){
                                DrawTextureRec(envItems[i].texture, envItems[i].frame, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, WHITE);
                            }else{
                                DrawTextureV(envItems[i].texture, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, WHITE);
                            }
                        }else
                            DrawRectangleRec(envItems[i].rect, envItems[i].color);
                    }
                    //conta os frames para animacao da lava
                    lavaTimer += GetFrameTime();
                    if(lavaTimer >= 0.6f){
                        lavaTimer=0;
                        lavaFrame++;
                    }
                    lavaFrame = lavaFrame % 4;
                    for (int i = 0; i < envItemsLength; i++){
                        if(envItems[i].hasTexture){
                            if(envItems[i].isLava){
                                envItems[i].frame.x = 32*lavaFrame;
                            }
                        }
                    }

                    drawPlayer(&player); //desenha o player 

                    EndMode2D();
                    EndDrawing();

                }

                UnloadTexture(sky);
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
                UnloadTexture(peao.texture);
                UnloadFont(font);
                UnloadFileText(text);
                UnloadFileText(text2);
                CloseWindow();

            } break;

            case CREDITS:
            {
                if ("./data/credits.txt" != NULL)
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
            case MENU:
            break;
        }

        framesCounter+=3; //a cada frame, (x) letras sao printadas,  quanto maior, mais rapido
        BeginDrawing();

        ClearBackground(SKYBLUE);
        DrawTextEx(font, "NIVAN no Nivanverso", (Vector2){175, 100}, 35, 8, YELLOW);
        DrawTextEx(font, TextSubtext("INICIAR - Enter\n CREDITOS - C", 0, framesCounter/5), (Vector2){260, 225}, 35, 8, BLACK);

        EndDrawing();
    }

                UnloadTexture(sky);
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
                CloseWindow();

    return 0;
}
