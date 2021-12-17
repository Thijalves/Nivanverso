#include "UnloadAllCarlos.h"
#include <stdio.h>
#include "raylib.h"


void UnloadAll(FILE **file, Texture2D *grassSingle, Texture2D *GrassIntenalEdgeL, Texture2D *lava, Texture2D *dirt, Texture2D *grassWallRight
,Texture2D *grassWallLeft, Texture2D *grassEdgeRight, Texture2D *grassEdgeLeft, Texture2D *grass, Texture2D *GrassIntenalEdgeD, Font *font, char **text, char **text2,  Texture2D *sky){
                UnloadTexture(*sky);
                UnloadTexture(*grassSingle);
                UnloadTexture(*GrassIntenalEdgeL);
                UnloadTexture(*GrassIntenalEdgeD);
                UnloadTexture(*grass);
                UnloadTexture(*grassEdgeLeft);
                UnloadTexture(*grassEdgeRight);
                UnloadTexture(*grassWallLeft);
                UnloadTexture(*grassWallRight);
                UnloadTexture(*lava);
                UnloadTexture(*GrassIntenalEdgeL);
                UnloadFont(*font);
                UnloadFileText(*text);
                UnloadFileText(*text2);
                CloseWindow();
}
