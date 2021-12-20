#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "enemyStruct.h"
#include "platformStruct.h"
#include "initiateCamera.h"
#include "initiatePlayer.h"
#include "drawPlayer.h"
#include "updatePlayer.h"
#include "updateCamera.h"
#include "loadAllHandlerCarlos.h"
#include "UnloadAllCarlos.h"
#include "clouds.h"
#include "floatingPlatform.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "audio.h"

typedef enum {
    MENU = 0,
    PLAY,
    CREDITS,
} Selection;

int main(void){   //ao mudar de animacao nos mudamos a largura e altura do frame e a textura

    char *text, *text2, *dialogIni;
    text = NULL, text2 = NULL, dialogIni = LoadFileText("./data/intro.txt");
    
    const int screenWidth = 900;
    const int screenHeight = 544;

    InitWindow(screenWidth, screenHeight, "Nivan no nivanverso");

    //fontes
    Font font, fontIntro;
    fontIntro= LoadFontEx("./assets/fonteIntro.ttf", 50, 0, 0);
    SetTextureFilter(fontIntro.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
    
    FILE *mapFile = NULL;
    
    //texturas
    Texture2D backgroundMenu, grassSingle, GrassIntenalEdgeL, lava, dirt, grassWallRight, grassWallLeft, grassEdgeRight, grassEdgeLeft, grass, GrassIntenalEdgeD, sky, nuvens[4];

    loadAll(&mapFile, &backgroundMenu, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD,
    &font, &text, &text2, &sky, nuvens);
    Texture2D singleBlock = LoadTexture("./textures/tilemap/miolinho.png");
    Texture2D grassTipR = LoadTexture("./textures/tilemap/subidaD.png");
    Texture2D grassTipL = LoadTexture("./textures/tilemap/subidaE.png");
    Texture2D hotel =  LoadTexture("./textures/hotel.png");
    Texture2D life =  LoadTexture("./textures/vida.png");

    //formacao do mapa ====================================================================================================================================================================================================================
    int mapWidth;

    fseek(mapFile, -5, SEEK_END);
    fscanf(mapFile, "%d", &mapWidth);
    EnvItem *envItems = (EnvItem *) malloc((mapWidth * 10) * sizeof(EnvItem));
    fseek(mapFile, 0, SEEK_SET);

    int posx = 0, posy = 0;
    for(int i = 0; i < mapWidth * 10; i++){
        char block;
        fscanf(mapFile, "%c", &block);
        switch(block){
            case 'e':
                envItems[i].texture = grassEdgeLeft;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture = 1;
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
                envItems[i].hasTexture = 1;
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
                envItems[i].hasTexture = 1;
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
                envItems[i].hasTexture = 1;
                envItems[i].isLava = 0;
                break;
            break;
            case 'm':
                envItems[i].texture = singleBlock;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture = 1;
                envItems[i].isLava = 0;
                break;
            break;
            case 'p':
                envItems[i].texture = grassTipL;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture = 1;
                envItems[i].isLava = 0;
                break;
            break;
            case 't':
                envItems[i].texture = grassTipR;
                envItems[i].color = BROWN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture = 1;
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
                envItems[i].hasTexture = 1;
                envItems[i].isLava = 0;
                break;
            case '^':
                envItems[i].texture = grass;
                envItems[i].color = GREEN;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture = 1;
                envItems[i].isLava = 0;
                break;
            case '@':
                envItems[i].texture = lava;
                envItems[i].color = RED;
                envItems[i].rect.width = 32;
                envItems[i].rect.height = 32;
                envItems[i].rect.x = posx;
                envItems[i].rect.y = posy;
                envItems[i].hasTexture = 1;
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

        if(posx % (mapWidth - 1) * 32 == 0 && posx != 0){
            posy += 32;
            posx = 0;
        } else posx += 32;
    }
    int envItemsLength = mapWidth*10;
    //===========================================================================================================================================================================================================

    //declaracao do player e dos NPCs===========================================================================================================================================================================================================
    Player player = {0};
    Npc navin = {0};
    Npc nivanocito = {0};
    Npc holmes = {0};
    
    //inicializa o player e os npcs
    nivanocito.sprite.texture = LoadTexture("./textures/nivanocito.png");
    nivanocito.dialogBox = LoadTexture("./textures/vinanCard.png");
    navin.sprite.texture = LoadTexture("./textures/navin.png");
    navin.dialogBox = LoadTexture("./textures/navinCard.png");
    holmes.sprite.texture = LoadTexture("./textures/nivanholmes.png");
    holmes.dialogBox = LoadTexture("./textures/holmesCard.png");
    Texture2D blank = LoadTexture("./textures/blank.png");
    initiateNpc(&navin, (Vector2){247, 220});
    initiateNpc(&nivanocito, (Vector2){2650, 61});
    initiateNpc(&holmes, (Vector2){9080, 93});
    initiatePlayer(&player);
    //===========================================================================================================================================================================================================

    //inicializa os inimigos===========================================================================================================================================================================================================
    //inicializa os peoes 
    Vector2 positionsPawns[] = {{2168, 120}, {2800, 184}, {3512, 184}, {5070, 248}, {6080, 250}, {6290, 250}, {8223, 218}};
    int pawnsLength = sizeof(positionsPawns)/sizeof(positionsPawns[0]);
    Enemy *pawns = (Enemy *)malloc(pawnsLength * sizeof(Enemy));
    for(int i = 0; i < pawnsLength; i++)
        initiatePawn(&pawns[i], positionsPawns[i]);

    //inicializa as torres 
    Vector2 positionsRooks[] = {{3030, 184}, {4200, 214}, {4870, 248}, {5270, 248}};
    int rooksLength = sizeof(positionsRooks)/sizeof(positionsRooks[0]);
    Enemy *rooks = (Enemy *)malloc(rooksLength * sizeof(Enemy));
    for(int i = 0; i < rooksLength; i++)
        initiateRook(&rooks[i], positionsRooks[i]);

    //inicializa os cavalos
    Vector2 positionsKnigth[] = {{7142, 207}, {8220, 214}};
    int knightLength = sizeof(positionsKnigth)/sizeof(positionsKnigth[0]);
    Enemy *knight = (Enemy *)malloc(knightLength * sizeof(Enemy));
    for(int i = 0; i < knightLength; i++)
        initiateKnight(&knight[i], positionsKnigth[i]);
        
    //===========================================================================================================================================================================================================
    
    //inicializa elementos dinamicos do cenario===========================================================================================================================================================================================================
    //inicializa nuvens
    int cloudsLength = 300;
    Clouds cloud[300] = {0};
    for(int i = 0; i < cloudsLength; i++){
        cloud[i].texture = nuvens[GetRandomValue(0, 3)];
        generateClouds(&cloud[i]);
    }
    //inicializar plataformas flutuantes 
    Vector2 positionsPlatforms[] = {{1680, 256}, {7592, 256}, {8720, 224}};
    int platformsLength = sizeof(positionsPlatforms)/sizeof(positionsPlatforms[0]);
    Platforms *platform = (Platforms *)malloc(platformsLength * sizeof(Platforms));
    for(int i = 0; i < platformsLength; i++)
        initiateFloatingPlatform(&platform[i], positionsPlatforms[i]);
    //===========================================================================================================================================================================================================
    
    //inicializa o audio===========================================================================================================================================================================================================
    Audio audio;
    InitAudioDevice();
    initiateAudio(&audio);
    PlayMusicStream(audio.game);
    PlayMusicStream(audio.menu);
    SetMusicVolume(audio.menu, 0.2);
    SetMusicVolume(audio.game, 0.2);
    //===========================================================================================================================================================================================================
    
    //declaracao de variaveis===========================================================================================================================================================================================================
    int pause = 0;
    int intro = 1;
    int creditToMenu = 0;
    int unload = 0;
    float navinY = 0;
    float nivanocitoY = 0;
    float holmesY = 0;
    //frames
    float yText = 400;
    int transp = 20;
    int flagMenu=0;
    int playerFrame = 0;
    int lavaFrame = 0;
    //variaveis do menu
    int framesCounter=0;
    Selection Option = MENU;
    //timers
    float playerTimer = 0;
    float pawnTimer = 0;
    float rookTimer = 0;
    float knightTimer = 0;
    float knightCount = 0; 
    float cloudTimer = 0;
    float lavaTimer = 0;
    float platformTimer = 0;

    int flagColor = 0;
    //===========================================================================================================================================================================================================         

    //camera===========================================================================================================================================================================================================
    Camera2D camera = { 0 };
    initiateCamera(&camera, player, screenWidth, screenHeight);
    //===========================================================================================================================================================================================================

    SetTargetFPS(60);

    //detecta o que foi pressionado
    char esc = 1;
    while ((!WindowShouldClose() || creditToMenu == 1) && esc){ // Detect window close button or ESC key
        creditToMenu = 0;
        switch(Option){
            case MENU:
                UpdateMusicStream(audio.menu);
                if(IsKeyPressed(KEY_ENTER)){
                    Option = PLAY; 
                    if(intro) pause = 2; 
                    else pause = 0;
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
                    if(player.playerState == 4) pause = 1; 
                    if(pause == 2){//texto introdutorio
                        while(yText > -480 && pause==2){
                        BeginDrawing();
                            intro = 0;
                            UpdateMusicStream(audio.game);
                            ClearBackground(SKYBLUE);
                            DrawTextureV(backgroundMenu, (Vector2){0,0}, (Color) {245,245,245,100});
                            DrawTextEx(fontIntro, dialogIni, (Vector2){145, yText}, 30, 4, BLACK);
                            if(IsKeyPressed(KEY_SPACE)){
                                PlaySound(audio.select);
                                pause = 0;
                            }
                            if(yText == -479){
                                while(transp<200){
                                    UpdateMusicStream(audio.game);
                                    BeginDrawing();
                                    transp++;
                                    DrawTextureV(blank, (Vector2){0,0}, (Color) {245,245,245,(unsigned char)transp});
                                    EndDrawing();
                                }
                                pause = 0;
                                transp = 200;
                            }
                            yText-=0.5;
                            if(WindowShouldClose()==1){
                                pause = 0;
                            }
                        EndDrawing();
                        }
                    }else if(pause == 0){//jogando
                        float deltaTime = GetFrameTime();
                        //updates
                        UpdateMusicStream(audio.game);
                        updateCamera(&camera, &player, screenWidth, screenHeight);
                        updatePlayer(&player, deltaTime, envItems, envItemsLength, platform, platformsLength, &audio);
                        if(player.position.x > 9400) pause = 3;

                        BeginDrawing();
                        BeginMode2D(camera);
                            ClearBackground((Color){58, 111, 247, 255});

                            //printf("Posicao x do player: %f\n", player.position.x);
                            //printf("Posicao y do player: %f\n", player.position.y);
                            
                            //movimento do peao===========================================================================================================================================================================================================
                            pawnTimer += GetFrameTime();
                            if(pawnTimer >= 0.02){
                                for(int i = 0; i < pawnsLength; i++){
                                    pawnTimer = 0;
                                    if(pawns[i].rectangle.x >= pawns[i].initialPosition.x + 54){
                                        pawns[i].direction = -1;
                                    }else if(pawns[i].rectangle.x <= pawns[i].initialPosition.x - 54){
                                        pawns[i].direction = 1;
                                    }
                                    pawns[i].rectangle.x += pawns[i].direction * pawns[i].speed * deltaTime;
                                }
                            }
                            //===========================================================================================================================================================================================================

                            //movimento da torre===========================================================================================================================================================================================================
                            rookTimer += GetFrameTime();
                            if(rookTimer >= 0.02){
                                for(int i = 0; i < rooksLength; i++){
                                    rookTimer = 0;
                                    if(fabs(player.position.x - rooks[i].rectangle.x) <= 128){
                                        if(player.position.x > rooks[i].rectangle.x && rooks[i].rectangle.x - rooks[i].initialPosition.x < 140){
                                            rooks[i].direction = 1;
                                            rooks[i].rectangle.x += rooks[i].direction * rooks[i].speed * deltaTime;
                                        }else if(player.position.x < rooks[i].rectangle.x && rooks[i].rectangle.x - rooks[i].initialPosition.x > -140){
                                            rooks[i].direction = -1;
                                            rooks[i].rectangle.x += rooks[i].direction * rooks[i].speed * deltaTime;
                                        }
                                    }
                                }
                            }
                            //===========================================================================================================================================================================================================

                            //movimento cavalo===========================================================================================================================================================================================================
                            knightTimer += GetFrameTime();
                            if(knightTimer >= 0.02){
                                for(int i = 0; i < knightLength; i++){
                                    knightTimer = 0;
                                    if(fabs(player.position.x - knight[i].rectangle.x) <= 128 && !knight[i].dashing){
                                        knight[i].dashing = 1;
                                        knightCount = 0; 
                                    }else knight[i].rectangle.y = 207;
                                    
                                    if(knight[i].dashing){
                                        knightCount += GetFrameTime();
                                        knight[i].rectangle.y = 160; //sobe
                                        //vai pra cima
                                        if(knightCount <= 0.3){
                                            if(player.position.x > knight[i].rectangle.x && knight[i].rectangle.x - knight[i].initialPosition.x < 224 ){                                    
                                                knight[i].direction = 1;
                                                knight[i].rectangle.x += knight[i].direction*knight[i].speed * deltaTime;
                                            }else if(player.position.x < knight[i].rectangle.x && knight[i].rectangle.x - knight[i].initialPosition.x > -224){
                                                knight[i].direction = -1;
                                                knight[i].rectangle.x += knight[i].direction*knight[i].speed * deltaTime;
                                            }
                                        }
                                        //timer para descer
                                        if(knightCount >= 0.4){
                                            knight[i].rectangle.y = 207;
                                            PlaySound(audio.knightFall);
                                            knight[i].dashing = 0;
                                        }
                                    }
                                }
                            }
                            //===========================================================================================================================================================================================================

                        
                            //colisao com inimigos===========================================================================================================================================================================================================
                            //colisao peao
                            for(int i = 0; i < pawnsLength; i++)
                                if(pawns[i].isAlive)
                                    hitPawn(&pawns[i], &player, &audio);
                                    
                            //colisao torre
                            for(int i = 0; i < rooksLength; i++)
                                if(rooks[i].isAlive)
                                    hitRook(&rooks[i], &player, &audio);
                                
                            //colisao cavalo
                            for(int i = 0; i < knightLength; i++)
                                if(knight[i].isAlive)
                                    hitKnight(&knight[i], &player, &audio);
                            
                            //===========================================================================================================================================================================================================

                            //animacoes===========================================================================================================================================================================================================
                            //player
                            playerTimer += GetFrameTime();
                            if(playerTimer >= 0.075f){
                                playerTimer = 0;
                                playerFrame++;
                            }
                            playerFrame = playerFrame % player.idle.maxFrames;
                            player.frame.x = (player.frame.width * playerFrame);

                            //NPCs
                            navin.frame.x = (navin.frame.width * playerFrame);
                            nivanocito.frame.x = (nivanocito.frame.width * playerFrame);                 
                            holmes.frame.x = (holmes.frame.width * playerFrame);   

                            //lava
                            lavaTimer += GetFrameTime();
                            if(lavaTimer >= 0.6f){
                                lavaTimer = 0;
                                lavaFrame++;
                            }
                            lavaFrame = lavaFrame % 4;
                            for (int i = 0; i < envItemsLength; i++){
                                if(envItems[i].hasTexture){
                                    if(envItems[i].isLava)
                                        envItems[i].frame.x = 32 * lavaFrame;
                                }
                            }      
                            //===========================================================================================================================================================================================================

                            //movimentacao===========================================================================================================================================================================================================
                            //nuvens
                            cloudTimer += GetFrameTime();
                            if(cloudTimer >= 0.02){
                                for(int i = 0; i < cloudsLength; i++){
                                    cloudTimer = 0;
                                    cloud[i].position.x += cloud[i].speed * deltaTime;
                                }
                            }
                            //plataformas flutuantes 
                            platformTimer += GetFrameTime();
                            if(platformTimer >= 0.01){
                                for(int i = 0; i < platformsLength; i++){
                                    platformTimer = 0;
                                    if(platform[i].rectangle.x >= platform[i].initialPosition.x + 128){
                                        platform[i].direction = -1;
                                    }else if(platform[i].rectangle.x <= platform[i].initialPosition.x - 128){
                                        platform[i].direction = 1;
                                    }
                                    
                                    platform[i].rectangle.x += platform[i].speed * platform[i].direction * deltaTime;
                                    if (platform[i].rectangle.x <= player.position.x + player.frame.width - 5 && //esquerda
                                        player.position.x <= platform[i].rectangle.x + platform[i].rectangle.width && //direita
                                        platform[i].rectangle.y >= player.position.y &&
                                        platform[i].rectangle.y < player.position.y + player.vSpeed * deltaTime){
                                        player.canJump = 1;
                                        player.vSpeed = 0.0f;
                                        player.position.y = platform[i].rectangle.y;
                                        player.position.x += platform[i].speed * platform[i].direction * deltaTime;
                                    }
                                    
                                }
                            }
                            //===========================================================================================================================================================================================================
                            
                            //desenhar===========================================================================================================================================================================================================
                            //ceu
                            DrawTextureV(sky, (Vector2){0,0}, WHITE);
                            //nuvem
                            for(int i = 0; i < cloudsLength; i++)
                                DrawTextureV(cloud[i].texture, cloud[i].position, WHITE);
                            //hotel
                            DrawTextureV(hotel, (Vector2){9384,  32}, WHITE);
                            //blocos
                            for (int i = 0; i < envItemsLength; i++){
                                if(envItems[i].hasTexture){
                                    if(envItems[i].isLava){
                                        DrawTextureRec(envItems[i].texture, envItems[i].frame, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, WHITE);
                                    }else{
                                        if(i == 1775){
                                            DrawTextureV(envItems[i].texture, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, (Color){255, 100, 200, 180});            
                                        }else{
                                            DrawTextureV(envItems[i].texture, (Vector2){envItems[i].rect.x,envItems[i].rect.y}, WHITE);
                                        }
                                    }
                                }else
                                    DrawRectangleRec(envItems[i].rect, WHITE);
                            }
                            //peoes
                            for(int i = 0; i < pawnsLength; i++)
                                if(pawns[i].isAlive)
                                    DrawTextureV(pawns[i].texture, (Vector2) {pawns[i].rectangle.x,pawns[i].rectangle.y}, WHITE);
                            //torres
                            for(int i = 0; i < rooksLength; i++)
                                if(rooks[i].isAlive)
                                    DrawTextureV(rooks[i].texture, (Vector2) {rooks[i].rectangle.x,rooks[i].rectangle.y}, WHITE);
                            //cavalos
                            for(int i = 0; i < knightLength; i++)
                                if(knight[i].isAlive)
                                    DrawTextureV(knight[i].texture, (Vector2) {knight[i].rectangle.x,knight[i].rectangle.y}, WHITE); 
                            //plataforma
                            for(int i = 0; i < platformsLength; i++)
                                DrawTextureV(platform[i].texture, (Vector2) {platform[i].rectangle.x, platform[i].rectangle.y}, WHITE);
                            //NPCs
                            DrawTextureRec(holmes.sprite.texture, (Rectangle){holmes.frame.x, holmes.frame.y, -holmes.frame.width, holmes.frame.height}, holmes.position, holmes.color);
                            DrawTextureRec(navin.sprite.texture, (Rectangle){navin.frame.x, navin.frame.y, -navin.frame.width, navin.frame.height}, navin.position, navin.color);
                            DrawTextureRec(nivanocito.sprite.texture, (Rectangle){nivanocito.frame.x, nivanocito.frame.y, -nivanocito.frame.width, nivanocito.frame.height}, nivanocito.position, nivanocito.color);
                            //player
                            drawPlayer(&player);
                            //===========================================================================================================================================================================================================
                        EndMode2D();
                            //desenho vida===========================================================================================================================================================================================================
                            if(fabs(player.position.x - navin.position.x) > 96 && fabs(player.position.x - nivanocito.position.x) > 96 && abs(player.position.x - holmes.position.x) > 96){
                                for(int i = 0; i < player.vida; i++){
                                    float lifeX = 35 * i;
                                    DrawTextureV(life, (Vector2){760 + lifeX, 40}, WHITE);
                                }
                            }
                            //===========================================================================================================================================================================================================
                            
                            //caixas de dialogo===========================================================================================================================================================================================================
                            //navin
                            if(fabs(player.position.x - navin.position.x) <= 96){
                                if(navinY < 32) navinY += 50 * deltaTime;
                                DrawTextureV(navin.dialogBox, (Vector2){100, navinY}, WHITE); 
                            }else navinY = 0;
                            //nivanocito
                            if(fabs(player.position.x - nivanocito.position.x) <= 96){
                                if(nivanocitoY < 32) nivanocitoY += 50 * deltaTime;
                                DrawTextureV(nivanocito.dialogBox, (Vector2){100, nivanocitoY}, WHITE); 
                            }else nivanocitoY = 0;
                            //holmes
                            if(fabs(player.position.x - holmes.position.x) <= 96){
                                if(holmesY < 32) holmesY += 50 * deltaTime;
                                DrawTextureV(holmes.dialogBox, (Vector2){100, holmesY}, WHITE); 
                            }else holmesY = 0;
                            //===========================================================================================================================================================================================================
                            //segunda transicao
                            if(transp>0){DrawTextureV(blank, (Vector2){0,0}, (Color) {245,245,245,(unsigned char)transp});transp--;} 
                        EndDrawing();
                    }else if(pause == 3){//tela de encerramento                      
                        playerTimer += GetFrameTime();
                        if(playerTimer >= 0.075f){
                            playerTimer=0;
                            playerFrame++;
                        }
                        playerFrame = playerFrame % player.idle.maxFrames;
                        player.frame.x = (player.frame.width*playerFrame);

                        //anima os NPCs
                        navin.frame.x = (navin.frame.width*playerFrame);
                        nivanocito.frame.x = (nivanocito.frame.width*playerFrame);                 
                        holmes.frame.x = (holmes.frame.width*playerFrame);         
                        
                        while(flagColor<200){
                                BeginDrawing();
                                {DrawTextureV(blank, (Vector2){0,0}, (Color) {245,245,245,(unsigned char)flagColor});flagColor++;}
                                EndDrawing();
                            }                        

                        //tela final 
                        BeginDrawing();
                            UpdateMusicStream(audio.menu);
                            ClearBackground(SKYBLUE);
                            DrawTextureV(backgroundMenu, (Vector2){0,0}, (Color) {245,245,245,200});
                            DrawTextEx(font, "YOU WIN", (Vector2){350, 170}, 50, 8, BLACK);
                            DrawTextEx(font, "  MENU - M\nSAIR - ESC", (Vector2){340, 300}, 35, 8, BLACK);
                            DrawTextureRec(holmes.sprite.texture, (Rectangle){holmes.frame.x, holmes.frame.y, -holmes.frame.width, holmes.frame.height}, (Vector2){315, 180}, holmes.color);
                            DrawTextureRec(navin.sprite.texture, (Rectangle){navin.frame.x, navin.frame.y, -navin.frame.width, navin.frame.height}, (Vector2){630, 180}, navin.color);
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
                        EndDrawing();
                    }else{ //jogo pausado
                        BeginDrawing();
                            if(player.vida == 0){ //morreu
                                UpdateMusicStream(audio.menu);
                                ClearBackground(SKYBLUE);
                                DrawTextureV(backgroundMenu, (Vector2){0,0}, (Color) {245,245,245,200});
                                DrawTextEx(font, "GAME OVER", (Vector2){260, 170}, 50, 8, BLACK);
                                DrawTextEx(font, "MENU - M", (Vector2){340, 280}, 35, 8, BLACK);
                                if(IsKeyPressed(KEY_M)){//voltar para o menu
                                    PlaySound(audio.select);
                                    Option = MENU;
                                    //reiniciar player e inimigos===========================================================================================================================================================================================================
                                    initiatePlayer(&player);
                                    for(int i = 0; i < pawnsLength; i++)
                                        initiatePawn(&pawns[i], positionsPawns[i]);
                                    for(int i = 0; i < rooksLength; i++)
                                        initiateRook(&rooks[i], positionsRooks[i]);
                                    for(int i = 0; i < knightLength; i++)
                                        initiateKnight(&knight[i], positionsKnigth[i]);
                                    //===========================================================================================================================================================================================================
                                    //restaurar
                                    player.playerState = 0;
                                    player.vida = 3;
                                    break;
                                }
                            }else if(player.vida > 0){ //dano
                                //renascer player
                                player.position.y = 100;
                                player.position.x -= 6*32;
                                player.vSpeed = 0;
                                player.playerState = 0;
                                Option = PLAY;
                                pause = 0;
                                player.color = WHITE;
                                unload = 1;
                            }
                        EndDrawing();
                    }
                }
                if((Option != MENU && unload == 0) || IsKeyPressed(KEY_ESCAPE) == 1) //esc pressionado, sair do jogo
                    esc = 0;
                unload = 0;
            } break;

            case CREDITS:
            {
                if ("./data/credits.txt" != NULL){
                    framesCounter = 0;
                    if (text2){
                        while(1){
                            framesCounter += 11;
                            UpdateMusicStream(audio.menu);
                            if(WindowShouldClose()){//apertando para sair volta para o menu
                                Option = MENU;
                                creditToMenu = 1;
                                break;
                            }
                            BeginDrawing();
                                ClearBackground(WHITE);
                                DrawTextEx(font, TextSubtext(text2, 0, framesCounter/1), (Vector2){190, 25}, 30, 8, BLACK);
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

        framesCounter += 3; //a cada frame, (x) letras do menu sao printadas,  quanto maior, mais rapido
        ClearBackground(SKYBLUE);
        
        //printa tela de menu
        BeginDrawing();
            if(transp>0 && flagMenu==1){DrawTextureV(blank, (Vector2){0,0}, (Color) {245,245,245,(unsigned char)transp});transp--;} 
            DrawTextureV(backgroundMenu, (Vector2){0,0}, (Color) {245,245,245,200});
            DrawTextEx(font, "NIVAN no Nivanverso", (Vector2){90, 100}, 45, 8, BLACK);
            DrawTextEx(font, TextSubtext("\nINICIAR - Enter\n  CREDITOS - C", 0, framesCounter/5), (Vector2){240, 255}, 35, 8, BLACK);
        EndDrawing();
    }

    //unload de tudo
    UnloadAll(&mapFile, &grassSingle, &GrassIntenalEdgeL, &lava, &dirt, &grassWallRight, &grassWallLeft, &grassEdgeRight, &grassEdgeLeft, &grass, &GrassIntenalEdgeD
    ,&font, &text, &text2, &sky);
    UnloadTexPlayer(&player);
    UnloadTexture(navin.sprite.texture);
    UnloadTexture(nivanocito.sprite.texture);
    UnloadTexture(nivanocito.dialogBox);
    UnloadTexture(navin.dialogBox);
    UnloadTexture(life);
    UnloadTexture(holmes.sprite.texture);
    UnloadTexture(holmes.dialogBox);
    UnloadTexture(knight->texture);
    UnloadTexture(blank);
    UnloadTexture(backgroundMenu);
    UnloadTexture(singleBlock);
    UnloadTexture(grassTipR);
    UnloadTexture(grassTipL);
    UnloadTexture(hotel);
    UnloadTexture(life);
    for(int i = 0; i < pawnsLength; i++) UnloadTexture(pawns[i].texture);
    for(int i = 0; i < platformsLength; i++) UnloadTexture(platform[i].texture);
    UnloadAudio(&audio);
    free(platform);
    free(rooks);
    free(pawns);
    free(envItems);
    free(knight);
    UnloadFont(fontIntro);
    UnloadFileText(dialogIni);
    UnloadSound(audio.select);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}