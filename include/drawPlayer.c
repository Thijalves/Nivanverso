#include "drawPlayer.h"

void drawPlayer(Player *player){

    Rectangle invertedFrame = player->frame;
    Vector2 position = {player->position.x, player->position.y - 35}; //desenha o player com correcao de altura

    invertedFrame.width = -player->frame.width; //frame com comprimento invertido

    //anima de acordo com o estado
    switch(player->playerState){
        case 0: //boneco parado
            if(player->facingDirection)
                DrawTextureRec(player->idle.texture, player->frame,  position, WHITE);
            else
                DrawTextureRec(player->idle.texture, invertedFrame,  position, WHITE);

            break;
        case 1: //andando p direita
            if(player->facingDirection)
                DrawTextureRec(player->run.texture, player->frame, position, WHITE);
            else
                DrawTextureRec(player->run.texture, invertedFrame, position, WHITE);
            break;
        case 2: //pulando p direita
            if(player->facingDirection)
                DrawTextureRec(player->jumping.texture, player->frame, position, WHITE);
            else
                DrawTextureRec(player->jumping.texture, invertedFrame, position, WHITE);
            break;
        case 3: //caindo p direita
            if(player->facingDirection)
                DrawTextureRec(player->falling.texture, player->frame, position, WHITE);
            else
                DrawTextureRec(player->falling.texture, invertedFrame, position, WHITE);
            break;
    }
}