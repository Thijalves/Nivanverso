#ifndef UPDATECAMERA_H
#define UPDATECAMERA_H

#include "raylib.h"
#include "structPlayer.h"

//Funcao para mover a camera (y fixo e x de acordo com o player)
void updateCamera(Camera2D *camera, Player *player, int screenWidth, int screenHeight){

    camera->offset = (Vector2){ (float)screenWidth/2, (float)screenHeight/2+6};

    float x, y;
    
    if(player->position.x <= 224){
        x = 225;
    }else if(player->position.x >= 3424){
        x = 3425;
    }else{
        x = player->position.x;
    }

    if(player->position.y <= 98){
        y = player->position.y-32;
    }else{
        y = (float)(screenHeight/2- 96);
    }

    camera->target = (Vector2){x, y};
    
    //(float)(screenHeight/2-48)
}

#endif