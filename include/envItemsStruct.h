#ifndef ENVITEMSSTRUCT_H
#define ENVITEMSSTRUCT_H

#include "raylib.h"
typedef struct EnvItem {
    Rectangle rect;
    Color color;
    Texture2D texture;
    char hasTexture;
} EnvItem;


#endif