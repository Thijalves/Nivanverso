#ifndef STRUCTPLAYER_H
#define STRUCTPLAYER_H

#include "raylib.h"

typedef struct {
    Texture2D texture;
    int width;
    int height;
    int maxFrames;
} Sprite;

typedef struct {
    Rectangle frame;
    Vector2 position;
    Sprite idle;
    Sprite run;
    Sprite runLeft;
    Sprite jumping;
    Sprite falling;
    Color color;
    float jumpS;
    float hSpeed;
    float vSpeed;
    char canJump;
    int playerState; // 0=idle 1=run 2 = jumping 3 = falling
    char facingDirection; //direita=1 esquerda=0
    int vida;
} Player;

typedef struct {
    Rectangle frame;
    Vector2 position;
    Sprite sprite;
    Color color;
} Npc;

#endif 