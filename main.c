#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
#include "rook.h"
#include "audio.h"
#include "platformStruct.h"
#include "floatingPlatform.h"
#include "clouds.h"

typedef enum {
    MENU = 0,
    PLAY,
    CREDITS,
} Selection;

int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura

    FILE *mapFile = NULL;
    char *text, *text2; text = NULL, text2 = NULL;
    
    //variaveis do menu
    int framesCounter=0;
    Selection Option = MENU;

    const int screenWidth = 900;
    const int screenHeight = 544;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    Font font;
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

    Texture2D grassSingle, GrassIntenalEdgeL, lava, dirt, grassWallRight, grassWallLeft, grassEdgeRight, grassEdgeLeft, grass, GrassIntenalEdgeD, sky, nuvens[4];

    loadAll(&mapFile, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD,
    &font, &text, &text2, &sky, nuvens);



    int mapWidth;

    fseek(mapFile, -5, SEEK_END);

    fscanf(mapFile, "%d", &mapWidth);

    printf("Largura do mapa: %d\n", mapWidth);

    // EnvItem envItems[3000];
    EnvItem *envItems = (EnvItem *) malloc((mapWidth*10) * sizeof(EnvItem));

    fseek(mapFile, 0, SEEK_SET);


    int posx = 0, posy = 0;
    for(int i = 0; i < mapWidth*10; i++){
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

        if(posx % (mapWidth-1)*32 == 0 && posx != 0){
            posy += 32;
            posx = 0;
        } else {
            posx += 32;
        }
    }

    // int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);
    int envItemsLength = mapWidth*10;

    //instancia o player com a animacao idle
    Player player = {0};
    Npc navin = {0};
    Npc nivanocito = {0};
    
    nivanocito.sprite.texture = LoadTexture("./textures/nivanocito.png");
    navin.sprite.texture = LoadTexture("./textures/navin.png");
    initiateNpc(&navin, (Vector2){247, 220});
    initiateNpc(&nivanocito, (Vector2){2650, 61});

    initiatePlayer(&player);
    
    int cloudsLength = 300;

    Clouds cloud[300] = {0};
    
    for(int i = 0; i < cloudsLength; i++){
        cloud[i].texture = nuvens[GetRandomValue(0, 3)];
        generateClouds(&cloud[i]);
    }
    
    
    //inicializar plataformas flutuantes 
    Vector2 positionsPlatforms[] = {{1680,256}};
    int platformsLength = sizeof(positionsPlatforms)/sizeof(positionsPlatforms[0]);
    // Platforms platform[2];
    Platforms *platform = (Platforms *)malloc(platformsLength * sizeof(Platforms));
    for(int i = 0; i < platformsLength; i++){
        initiateFloatingPlatform(&platform[i], positionsPlatforms[i]);
    }

    //inicializa as torres 
    Vector2 positionsRooks[] = {{3030, 184}, {4200, 214}, {4870, 248}, {5270, 248}};
    int rooksLength = sizeof(positionsRooks)/sizeof(positionsRooks[0]);
    // Enemy rooks[2];
    Enemy *rooks = (Enemy *)malloc(rooksLength * sizeof(Enemy));
    for(int i = 0; i < rooksLength; i++){
        initiateRook(&rooks[i], positionsRooks[i]);
    }

    //inicializa os peoes 
    Vector2 positionsPawns[] = {{2200,120}, {2800,184}, {3512, 184}, {5070, 248}};
    int pawnsLength = sizeof(positionsPawns)/sizeof(positionsPawns[0]);
    // Enemy pawns[2];
    Enemy *pawns = (Enemy *)malloc(pawnsLength * sizeof(Enemy));
    for(int i = 0; i < pawnsLength; i++){
        initiatePawn(&pawns[i], positionsPawns[i]);
    }
    //Iniciar audio
    Audio audio;
    InitAudioDevice();
    initiateAudio(&audio);
    PlayMusicStream(audio.game);
    PlayMusicStream(audio.menu);
    SetMusicVolume(audio.menu, 0.1);
    SetMusicVolume(audio.game, 0.1);
    
    int playerFrame = 0;
    int lavaFrame = 0;

    float playerTimer = 0;
    float platformTimer = 0;
    float torreTimer = 0;
    float pawnTimer = 0;
    float lavaTimer = 0;
    float cloudTimer = 0;
    int pause = 0;
    int c = 0;


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
                UpdateMusicStream(audio.menu);
                if(IsKeyPressed(KEY_ENTER)){
                    Option = PLAY; pause = 0;
                    PlaySound(audio.select);
                } else if(IsKeyPressed(KEY_C)){
                    Option = CREDITS;
                    PlaySound(audio.select);
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
                        UpdateMusicStream(audio.game);
                        float deltaTime = GetFrameTime();
                        updateCamera(&camera, &player, screenWidth, screenHeight);
                        updatePlayer(&player, deltaTime, envItems, envItemsLength, platform, platformsLength, &audio);

                        BeginDrawing();
                        BeginMode2D(camera);
                        ClearBackground((Color){ 58, 111, 247, 255 });

                        // printf("Posicao x do player: %f\n", player.position.x);
                        // printf("Posicao y do player: %f\n", player.position.y);

                        //movimento das plataformas 
                        platformTimer += GetFrameTime();
                        if(platformTimer >= 0.01){
                            for(int i = 0; i < platformsLength; i++){
                                platformTimer = 0;
                                if(platform[i].rectangle.x >= platform[i].initialPosition.x+128){
                                    platform[i].direction = -1;
                                }else if(platform[i].rectangle.x <= platform[i].initialPosition.x-128){
                                    platform[i].direction = 1;
                                }
                                
                                platform[i].rectangle.x += platform[i].speed*platform[i].direction*deltaTime;
                                if (platform[i].rectangle.x <= player.position.x+player.frame.width-5 && //esquerda
                                    player.position.x <= platform[i].rectangle.x+platform[i].rectangle.width && //direita
                                    platform[i].rectangle.y >= player.position.y &&
                                    platform[i].rectangle.y < player.position.y + player.vSpeed*deltaTime){
                                    player.canJump = 1;
                                    player.vSpeed = 0.0f;
                                    player.position.y = platform[i].rectangle.y;
                                    player.position.x += platform[i].speed*platform[i].direction*deltaTime;
                                }
                                
                            }
                        }

                        //hora da torreeeee
                        torreTimer += GetFrameTime();
                        //move  o inimigo
                        if(torreTimer >= 0.02){
                            for(int i = 0; i < rooksLength; i++){
                                torreTimer = 0;
                                if(fabs(player.position.x - rooks[i].rectangle.x) <= 128){
                                    if(player.position.x > rooks[i].rectangle.x && rooks[i].rectangle.x - rooks[i].initialPosition.x < 140){
                                        rooks[i].direction = 1;
                                        rooks[i].rectangle.x += rooks[i].direction*rooks[i].speed*deltaTime;
                                    }else if(player.position.x < rooks[i].rectangle.x && rooks[i].rectangle.x - rooks[i].initialPosition.x > -140){
                                        rooks[i].direction = -1;
                                        rooks[i].rectangle.x += rooks[i].direction*rooks[i].speed*deltaTime;
                                    }
                                }
                            }
                        }

                        pawnTimer += GetFrameTime();
                        //move  o inimigo
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

                        for(int i = 0; i < rooksLength; i++){
                            if(rooks[i].isAlive){
                                hitRook(&rooks[i], &player, &audio);
                            }
                        }

                        for(int i = 0; i < pawnsLength; i++){
                            if(pawns[i].isAlive){
                                hitPawn(&pawns[i], &player, &audio);
                            }
                        }

                        //conta os frames para animacao do player
                        playerTimer += GetFrameTime();
                        if(playerTimer >= 0.075f){
                            playerTimer=0;
                            playerFrame++;
                        }
                        playerFrame = playerFrame % player.idle.maxFrames;
                        player.frame.x = (player.frame.width*playerFrame);

                        navin.frame.x = (navin.frame.width*playerFrame);
                        nivanocito.frame.x = (nivanocito.frame.width*playerFrame);                 

                        cloudTimer += GetFrameTime();
                        //move  o inimigo
                        if(cloudTimer >= 0.02){
                            for(int i = 0; i < cloudsLength; i++){
                                cloudTimer = 0;
                                cloud[i].position.x += cloud[i].speed*deltaTime;
                            }
                        }

                        DrawTextureV(sky, (Vector2){0,0}, WHITE);

                        for(int i = 0; i < cloudsLength; i++){
                            DrawTextureV(cloud[i].texture, cloud[i].position, WHITE);
                        }

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

                        //desenha os peoes
                        for(int i = 0; i < pawnsLength; i++){
                            if(pawns[i].isAlive){
                                DrawTextureV(pawns[i].texture, (Vector2) {pawns[i].rectangle.x,pawns[i].rectangle.y}, WHITE);
                            }
                        }

                        //desenha as torres
                        for(int i = 0; i < rooksLength; i++){
                            if(rooks[i].isAlive){
                                DrawTextureV(rooks[i].texture, (Vector2) {rooks[i].rectangle.x,rooks[i].rectangle.y}, WHITE);
                            }
                        }

                        //desenha a plataforma
                        for(int i = 0; i < platformsLength; i++){
                            DrawTextureV(platform[i].texture, (Vector2) {platform[i].rectangle.x, platform[i].rectangle.y}, WHITE);
                        }


                        DrawTextureRec(navin.sprite.texture, (Rectangle){navin.frame.x, navin.frame.y, -navin.frame.width, navin.frame.height}, navin.position, navin.color);
                        DrawTextureRec(nivanocito.sprite.texture, (Rectangle){nivanocito.frame.x, nivanocito.frame.y, -nivanocito.frame.width, nivanocito.frame.height}, nivanocito.position, nivanocito.color);
                        drawPlayer(&player); //desenha o player
                        
                        EndMode2D();
                        DrawText(TextFormat("VIDAS: %d", player.vida), 760, 40, 20, RAYWHITE);
                        EndDrawing();
                    } else {
                        //jogo pausado
                        BeginDrawing();
                        if(player.vida == 0){
                            UpdateMusicStream(audio.menu);
                            ClearBackground(SKYBLUE);
                            DrawTextEx(font, "GAME OVER\n\n MENU - M", (Vector2){300, 170}, 35, 8, BLACK);
                            if(IsKeyPressed(KEY_M)){
                                PlaySound(audio.select);
                                Option = MENU;
                                initiatePlayer(&player);
                                for(int i = 0; i < pawnsLength; i++){
                                    initiatePawn(&pawns[i], positionsPawns[i]);
                                } 
                                for(int i = 0; i < rooksLength; i++){
                                    initiateRook(&rooks[i], positionsRooks[i]);
                                }player.playerState = 0;
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
                    UnloadTexPlayer(&player);
                    UnloadTexture(navin.sprite.texture);
                    UnloadTexture(nivanocito.sprite.texture);
                    for(int i = 0; i < pawnsLength; i++) UnloadTexture(pawns[i].texture);
                    for(int i = 0; i < platformsLength; i++) UnloadTexture(platform[i].texture);
                    UnloadAudio(&audio);
                    free(platform);
                    free(rooks);
                    free(pawns);
                    free(envItems);
                    UnloadSound(audio.select);
                    CloseAudioDevice();
                    CloseWindow();
                }c=0;
            } break;

            case CREDITS:
            {
                if ("./data/credits.txt" != NULL){
                    framesCounter=0;
                    if (text2){
                        while(1){
                            framesCounter+=11;
                            UpdateMusicStream(audio.menu);
                            if(WindowShouldClose()){
                                Option = MENU;
                                help = 1;
                                break;
                            }
                            BeginDrawing();
                            ClearBackground(WHITE);
                            DrawTextEx(font, TextSubtext(text2, 0, framesCounter/1), (Vector2){290, 0}, 30, 8, BLACK);
                            DrawText("RETORNAR (ESC) -->", 80, 500, 20, DARKBLUE);
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
            DrawTextEx(font, TextSubtext("\nINICIAR - Enter\n CREDITOS - C", 0, framesCounter/5), (Vector2){240, 255}, 35, 8, BLACK);

        EndDrawing();
    }

                    UnloadAll(&mapFile, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD
                    ,&font, &text, &text2, &sky);

                    UnloadTexPlayer(&player);
                    UnloadTexture(navin.sprite.texture);
                    UnloadTexture(nivanocito.sprite.texture);
                    for(int i = 0; i < pawnsLength; i++) UnloadTexture(pawns[i].texture);
                    for(int i = 0; i < platformsLength; i++) UnloadTexture(platform[i].texture);
                    UnloadAudio(&audio);
                    free(platform);
                    free(rooks);
                    free(pawns);
                    free(envItems);
                    UnloadSound(audio.select);
                    CloseAudioDevice();
                    CloseWindow();
    return 0;
}