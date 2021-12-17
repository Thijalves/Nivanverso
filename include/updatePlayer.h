#ifndef UPDATEPLAYER_H
#define UPDATEPLAYER_H

#include "raylib.h"
#include "structPlayer.h"
#include "envItemsStruct.h"
#include "audio.h"

#define gravity 350

//Funcao pra atualizar as variaveis do player
void updatePlayer(Player *player, float deltaTime, EnvItem *envItems, int envItemsLength, Audio *audio);

#endif