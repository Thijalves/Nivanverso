#ifndef CLOUDS_H
#define CLOUDS_H

#include "raylib.h"

typedef struct{
    Vector2 position;
    Texture2D texture;
    int direction;
    float speed;
} Clouds;

void generateClouds(Clouds *clouds);


#endif