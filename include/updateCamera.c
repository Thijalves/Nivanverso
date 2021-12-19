#include "updateCamera.h"

void updateCamera(Camera2D *camera, Player *player, int screenWidth, int screenHeight){

    camera->offset = (Vector2){ (float)screenWidth/2, (float)screenHeight/2+6};

    float x, y;
    
    if(player->position.x <= 224){
        x = 225;
    }else if(player->position.x >= 9260){
        x = 9260;
    }else{
        x = player->position.x;
    }

    if(player->position.y <= 128){
        y = player->position.y-16;
    }else{
        y = (float)(screenHeight/2-96);
    }

    camera->target = (Vector2){x, y};
    
    //(float)(screenHeight/2-48)
}