#ifndef INITIATEPLAYER_H
#define INITIATEPLAYER_H

#include "raylib.h"
#include "structPlayer.h"

void initiatePlayer(Player *player);

void initiateNpc(Npc *npc, Vector2 position);

void UnloadTexPlayer(Player *player);

#endif