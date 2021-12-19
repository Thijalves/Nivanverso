#include "loadAllHandlerCarlos.h"
#include <stdio.h>
#include "raylib.h"

void loadAll(FILE **file, Texture2D *backgroundMenu, Texture2D *grassSingle, Texture2D *GrassIntenalEdgeL, Texture2D *lava, Texture2D *dirt, Texture2D *grassWallRight
             ,Texture2D *grassWallLeft, Texture2D *grassEdgeRight, Texture2D *grassEdgeLeft, Texture2D *grass, Texture2D *GrassIntenalEdgeD, Font *font, char **text, char **text2, Texture2D *sky
            , Texture2D *nuvens){
    FILE *mapFile = fopen("./data/fase32.txt","r");
    // FILE *mapFile = fopen("./data/faseTeste.txt","r");
    
    if(mapFile == NULL)
        printf("erro ao abrir arquivo\n");
    else
        *file = mapFile;

    Texture2D nuvensHold[4];
    nuvensHold[0] = LoadTexture("./textures/nuvempequena.png");
    nuvensHold[1] = LoadTexture("./textures/nuvemmedia.png");
    nuvensHold[2] = LoadTexture("./textures/nuvemgrande.png");
    nuvensHold[3] = LoadTexture("./textures/nuvemenorme.png");

    nuvens[0] = nuvensHold[0];
    nuvens[1] = nuvensHold[1];
    nuvens[2] = nuvensHold[2];
    nuvens[3] = nuvensHold[3];

    Texture2D background = LoadTexture("./textures/backgroundMenu.png");
    *backgroundMenu = background;
    Texture2D grassAlone = LoadTexture("./textures/tilemap/miolinho.png");
    *grassSingle = grassAlone;
    Texture2D InternalGrass = LoadTexture("./textures/tilemap/subidaE.png");
    *GrassIntenalEdgeL = InternalGrass;
    Texture2D lavaHold = LoadTexture("./textures/tilemap/lava.png");
    *lava = lavaHold;
    Texture2D dirtHold = LoadTexture("./textures/tilemap/terra.png");
    *dirt = dirtHold;
    Texture2D grassWallRightHold = LoadTexture("./textures/tilemap/gramaD.png");
    *grassWallRight = grassWallRightHold;
    Texture2D grassWallLeftHold = LoadTexture("./textures/tilemap/gramaE.png");
    *grassWallLeft = grassWallLeftHold;
    Texture2D grassEdgeRightHold = LoadTexture("./textures/tilemap/curvaD.png");
    *grassEdgeRight = grassEdgeRightHold;
    Texture2D grassEdgeLeftHold = LoadTexture("./textures/tilemap/curvaE.png");
    *grassEdgeLeft = grassEdgeLeftHold;
    Texture2D grassHold = LoadTexture("./textures/tilemap/grama.png");
    *grass = grassHold;
    Texture2D GrassIntenalEdgeDHold = LoadTexture("./textures/tilemap/subidaD.png");
    *GrassIntenalEdgeD = GrassIntenalEdgeDHold;
    Font fontHold = LoadFontEx("./assets/font1.ttf", 50, 0, 0);
    *font = fontHold;
    char *textHold = LoadFileText("./data/about.txt");
    *text = textHold;
    char *text2Hold = LoadFileText("./data/credits.txt");
    *text2 = text2Hold;
    Texture2D skyHold = LoadTexture("./textures/ceu.png");
    *sky = skyHold;
}
