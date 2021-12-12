#ifndef INITIATECAMERA_H
#define INITIATECAMERA_H

#include "raylib.h"
#include "structPlayer.h"

void initiateCamera(Camera2D *camera, Player player, int screenWidth, int screenHeight){
    camera->target = player.position;
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f};
    camera->rotation = 0.0f;
    camera->zoom = 2.0f;
}

#endif