#ifndef ENEMYSTRUCT_H
#define ENEMYSTRUCT_H

#include "raylib.h"

typedef struct {
    Rectangle rectangle;
    Texture2D texture;
    int speed;
    char type;
    char isAlive;
    Vector2 initialPosition;
    char direction; //-1 esquerda | 1 direita
    Color color;
    char dashing;
} Enemy;

#endif