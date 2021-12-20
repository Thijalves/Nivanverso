#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

typedef struct{
    Music menu;
    Music game;
    Sound damage;
    Sound select;
    Sound jump;
    Sound fall;
    Sound step;
    Sound enemyDeath;
    Sound knightFall;
} Audio;

void initiateAudio(Audio *audio);

void UnloadAudio(Audio *audio);

#endif