#include "raylib.h"
#include <stdio.h>
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "enemyStruct.h"
#include "updatePlayer.h"
#include "drawPlayer.h"
#include "updateCamera.h"
#include "initiatePlayer.h"
#include "initiateCamera.h"
#include "loadAllHandlerCarlos.h"
#include "UnloadAllCarlos.h"
#include "pawn.h"
#include "audio.h"

typedef enum {
    MENU = 0,
    PLAY,
    CREDITS,
} Selection;

int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura

    FILE *mapFile = NULL;
    char *text, *text2; text = NULL, text2 = NULL;
    float pawnTimer = 0;
    float lavaTimer = 0;
    int lavaFrame = 0;
    int pause = 0;
    int c = 0;

    //variaveis do menu
    int framesCounter=0;
    Selection Option = MENU;

    //generateMap();

    const int screenWidth = 900;
    const int screenHeight = 544;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    int mapWidth;

    fseek(mapFile, -11, SEEK_END);

    fscanf(mapFile, "width: %d", &mapWidth);

    printf("Largura do mapa: %d\n", mapWidth);

    EnvItem envItems[3000];

    fseek(mapFile, 0, SEEK_SET);


    Font font;
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

    Texture2D grassSingle, GrassIntenalEdgeL, lava, dirt, grassWallRight, grassWallLeft, grassEdgeRight, grassEdgeLeft, grass, GrassIntenalEdgeD, sky;
    loadAll(&mapFile, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD, 
    &font, &text, &text2, &sky);

    int posx = 0, posy = 0;
    for(int i = 0; i < 3000; i++){
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

        if(posx % 299*32 == 0 && posx != 0){
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

    //Iniciar o peao
    //Enemy pawn = {0};
    //initiatePawn(&pawn, (Vector2){256, 216});

    Vector2 positions[] = {{256, 216}, {2200,120}};
    int pawnsLength = sizeof(positions)/sizeof(positions[0]);
    Enemy pawns[2];
    for(int i = 0; i < pawnsLength; i++){
        initiatePawn(&pawns[i], positions[i]);
    }
    //Iniciar audio
    Audio audio;
    InitAudioDevice();
    //audio.select = LoadSound("audio/selection.mp3");

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
                    Option = PLAY; pause = 0;
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
                    if(player.playerState == 4) pause = 1, Option = MENU;

                    if(!pause){
                        float deltaTime = GetFrameTime();
                        updateCamera(&camera, &player, screenWidth, screenHeight);
                        updatePlayer(&player, deltaTime, envItems, envItemsLength, &audio);
                        
                        BeginDrawing();
                        BeginMode2D(camera);
                        DrawText("Vidas", GetScreenWidth()/2, GetScreenHeight()/2, 20, BLACK);
                        ClearBackground((Color){ 58, 111, 247, 255 });
                        //DarkBlue{ 0, 82, 172, 255 } Blue{{ 0, 121, 241, 255 }}

                        pawnTimer += GetFrameTime();
                        
                        //Desenha o inimigo
                        if(pawnTimer >= 0.02){
                            for(int i = 0; i < pawnsLength; i++){
                                pawnTimer = 0; 
                                if(pawns[i].rectangle.x >= pawns[i].initialPosition.x + 54){
                                    pawns[i].direction = -1;
                                }else if(pawns[i].rectangle.x <= pawns[i].initialPosition.x - 54){
                                    pawns[i].direction = 1;
                                }
                                pawns[i].rectangle.x += pawns[i].direction*pawns[i].speed*deltaTime;
                            }
                        }
                        
                        for(int i = 0; i < pawnsLength; i++){
                            if(pawns[i].isAlive){
                                hitPawn(&pawns[i], &player, &audio);
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

                        
                        // DrawTextureV(pawn.texture, (Vector2) {pawn.rectangle.x,pawn.rectangle.y}, WHITE);    

                        //for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color); //desenha os obstaculos
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
                        for(int i = 0; i < pawnsLength; i++){
                            if(pawns[i].isAlive){
                                DrawTextureV(pawns[i].texture, (Vector2) {pawns[i].rectangle.x,pawns[i].rectangle.y}, WHITE);
                            }
                        }

                        EndMode2D();
                        DrawText(TextFormat("VIDAS: %d", player.vida), 760, 40, 20, RAYWHITE);
                        EndDrawing();
                    } else {
                        //jogo pausado
                        BeginDrawing();
                        if(player.vida == 0){
                            DrawText("MORREU FIOTE\nMENU - M\n", GetScreenWidth()/2, GetScreenHeight()/2, 20, BLACK);
                            if(IsKeyPressed(KEY_M)){
                                Option = MENU;
                                initiatePlayer(&player);
                                player.playerState = 0;
                                player.vida = 3;
                                break;
                            }
                        }else if(player.vida>0){
                            player.position.y = 100;
                            if(player.position.x>=160){player.position.x -= 96;}
                            player.vSpeed = 0;
                            player.playerState = 0;
                            Option = PLAY;
                            pause = 0;
                            player.color = WHITE;
                            c = 1;
                        }
                        EndDrawing();
                    }
                }
                if((Option!=MENU && c==0) || IsKeyPressed(KEY_ESCAPE)==1){
                    UnloadAll(&mapFile, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD
                    ,&font, &text, &text2, &sky);
                    UnloadTexture(player.idle.texture);
                    UnloadTexture(player.run.texture);
                    UnloadTexture(player.runLeft.texture);
                    UnloadTexture(player.falling.texture);
                    UnloadTexture(player.jumping.texture);
                    for(int i = 0; i < pawnsLength; i++) UnloadTexture(pawns[i].texture);
                    UnloadSound(audio.jump);
                    CloseAudioDevice();
                    CloseWindow();
                }c=0;
            } break;

            case CREDITS:
            {
                if ("./data/credits.txt" != NULL){
                    
                    if (text2){
                        while(!WindowShouldClose()){
                            if(IsKeyPressed(KEY_ESCAPE)){
                                Option = MENU;
                                help = 1;
                                break;
                            }
                            BeginDrawing();
                            ClearBackground(WHITE);
                            DrawText(text2, 190, 200, 20, BLUE);
                            DrawText("E - fechar\nESC - retornar", 400, 250, 20, BLACK);
                            EndDrawing();
                        }
                    }
                }
            } break;
            case MENU:
                {}
            break;
        }

        framesCounter+=3; //a cada frame, (x) letras sao printadas,  quanto maior, mais rapido
        BeginDrawing();

            ClearBackground(SKYBLUE);
            DrawTextEx(font, "NIVAN no Nivanverso", (Vector2){175, 100}, 35, 8, YELLOW);
            DrawTextEx(font, TextSubtext("INICIAR - Enter\n CREDITOS - C", 0, framesCounter/5), (Vector2){260, 225}, 35, 8, BLACK);

        EndDrawing();
    }

                if(Option!=MENU && c==0){

                    UnloadAll(&mapFile, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD
                    ,&font, &text, &text2, &sky);

                    UnloadTexture(player.idle.texture);
                    UnloadTexture(player.run.texture);
                    UnloadTexture(player.runLeft.texture);
                    UnloadTexture(player.falling.texture);
                    UnloadTexture(player.jumping.texture);
                    for(int i = 0; i < pawnsLength; i++) UnloadTexture(pawns[i].texture);
                    UnloadSound(audio.jump);
                    CloseAudioDevice();
                    CloseWindow();
                }

    return 0;
}
