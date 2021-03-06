#include "pawn.h"
#include "audio.h"

void initiatePawn(Enemy *pawn, Vector2 position){
    pawn->texture = LoadTexture("./textures/inimigo/peao.png");
    pawn->rectangle.x = position.x;
    pawn->initialPosition.x = pawn->rectangle.x;

    pawn->rectangle.y = position.y;
    pawn->initialPosition.y = pawn->rectangle.y;

    pawn->rectangle.width = 20;
    pawn->rectangle.height = 40;
    pawn->direction = 1;
    pawn->speed = 75;
    pawn->color = ORANGE;
    pawn->isAlive = 1;
}
void hitPawn(Enemy *pawn, Player *player, Audio *audio){

    if(player->position.x + player->frame.width >= pawn->rectangle.x &&
        player->position.x <= pawn->rectangle.x + pawn->rectangle.width &&
        player->position.y >= pawn->rectangle.y){

        if(player->position.y - pawn->rectangle.y < 5){
            pawn->isAlive = 0;
            PlaySound(audio->enemyDeath);
            player->vSpeed = -player->jumpS;
        }else{
            player->vida--;
            if(player->vida != 0) PlaySound(audio->damage);
            player->color = GRAY;
            player->vSpeed = -player->jumpS/2;
            player->playerState = 4;
        }

    }
}
