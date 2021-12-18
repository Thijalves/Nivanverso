#ifndef PLATFORMSTRUCT_H
#define PLATFORMSTRUCT_H

#include "raylib.h"

typedef struct {
    Rectangle rectangle;
    Texture2D texture;
    int speed;
    Vector2 initialPosition;
    char direction; //-1 esquerda | 1 direita
} Platform;


#endif