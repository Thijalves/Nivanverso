#ifndef PAWN_H
#define PAWN_H

#include "raylib.h"
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "enemyStruct.h"
#include "audio.h"

void initiatePawn(Enemy *pawn, Vector2 position);

//verificar colisao com peao
void hitPawn(Enemy *pawn, Player *player, Audio *audio);

#endif