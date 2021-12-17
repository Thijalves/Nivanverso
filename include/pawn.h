#ifndef PAWN_H
#define PAWN_H

#include "raylib.h"
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "enemyStruct.h"

void initiatePawn(Enemy *pawn, Player *player);

//verificar colisao com peao
void hitPawn(Enemy *pawn, Player *player);

#endif