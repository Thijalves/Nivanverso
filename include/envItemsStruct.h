#ifndef ENVITEMSSTRUCT_H
#define ENVITEMSSTRUCT_H

#include "raylib.h"
typedef struct EnvItem {
    Rectangle rect;
    Rectangle frame;
    Color color;
    Texture2D texture;
    char hasTexture;
    char isLava;
} EnvItem;


#endif