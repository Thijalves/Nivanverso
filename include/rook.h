#ifndef ROOK_H
#define ROOK_H

#include "raylib.h"
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "enemyStruct.h"
#include "audio.h"

void initiateRook(Enemy *rook, Vector2 position);

//verificar colisao com a torre
void hitRook(Enemy *rook, Player *player, Audio *audio);


#endif