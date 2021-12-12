#include "raylib.h"
#include <stdio.h>
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "updatePlayer.h"
#include "drawPlayer.h"
#include "updateCamera.h"
#include "initiatePlayer.h"
#include "initiateCamera.h"

typedef enum {
    MENU = 0,
    PLAY,
    CREDITS,
} Selection;


int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura


    //variaveis do menu
    int framesCounter=0;
    Selection Option = MENU;

    //carerga os arquivos de mapa
    FILE *mapFile = fopen("./fase.txt","r");
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

    Texture2D grassSingle = LoadTexture("./tilemap/milinho.png");
    Texture2D GrassIntenalEdgeL = LoadTexture("./resources/tilemap/subidaE.png");
    Texture2D GrassIntenalEdgeD = LoadTexture("./resources/tilemap/subidaD.png");
    Texture2D grass = LoadTexture("./resources/tilemap/grama.png");
    Texture2D grassEdgeLeft = LoadTexture("./resources/tilemap/curvaE.png");
    Texture2D grassEdgeRight = LoadTexture("./resources/tilemap/curvaD.png");
    Texture2D grassWallLeft = LoadTexture("./resources/tilemap/gramaE.png");
    Texture2D grassWallRight = LoadTexture("./resources/tilemap/gramaD.png");
    Texture2D dirt = LoadTexture("./resources/tilemap/terra.png");
    Texture2D lava = LoadTexture("./resources/tilemap/lava.png");


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

    //carrega a fonte
    Font font = LoadFontEx("./assets/font1.ttf", 50, 0, 0);
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

    //carrega o .txt
    char *text; text = NULL;
    text = LoadFileText("./data/about.txt");

    char *text2; text2 = NULL;
    text2 = LoadFileText("./data/credits.txt");


    float timer = 0;
    int frame = 0;

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

                    //for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //desenhna os obstaculos
                    for (int i = 0; i < envItemsLength; i++){
                        if(envItems[i].hasTexture)
                            DrawTextureV(envItems[i].texture, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, WHITE);
                        else
                            DrawRectangleRec(envItems[i].rect, envItems[i].color);
                    }
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
