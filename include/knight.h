#ifndef KNIGHT_H
#define KNIGHT_H

#include "raylib.h"
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "enemyStruct.h"
#include "audio.h"

void initiateKnight(Enemy *knight, Vector2 position);

//verificar colisao com peao
void hitKnight(Enemy *knight, Player *player, Audio *audio);

#endif