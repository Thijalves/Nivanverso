#include "pawn.h"
#include "audio.h"

void initiatePawn(Enemy *pawn, Vector2 position){
    pawn->texture = LoadTexture("./textures/inimigo/peao.png");
    // pawn->rectangle.x = player->position.x + 64;
    // pawn->rectangle.x = player->position.x + 256;
    pawn->rectangle.x = position.x;
    // pawn->initialPosition.x = pawn->rectangle.x + 192;
    pawn->initialPosition.x = pawn->rectangle.x;

    pawn->rectangle.y = position.y;
    pawn->initialPosition.y = pawn->rectangle.y;

    pawn->rectangle.width = 20;
    pawn->rectangle.height = 40;
    pawn->direction = 1;
    pawn->speed = 50;
    pawn->color = ORANGE;
}
void hitPawn(Enemy *pawn, Player *player, Audio *audio){
    audio->jump = LoadSound("audio/jump.mp3");
    if(player->position.x + player->frame.width >= pawn->rectangle.x &&
        player->position.x <= pawn->rectangle.x + pawn->rectangle.width &&
        player->position.y >= pawn->rectangle.y){

        if(player->position.y - pawn->rectangle.y < 5){
            player->vSpeed = -player->jumpS;
            PlaySound(audio->jump);
        }else{
            player->color = GRAY;
            player->vida--;
            player->vSpeed = -player->jumpS/2;
            player->playerState = 4;
        }

    }
}
