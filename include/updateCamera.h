#ifndef UPDATECAMERA_H
#define UPDATECAMERA_H

#include "raylib.h"
#include "structPlayer.h"

//Funcao para mover a camera (y fixo e x de acordo com o player)
void updateCamera(Camera2D *camera, Player *player, int screenWidth, int screenHeight);

#endif