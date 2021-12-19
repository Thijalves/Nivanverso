#include "rook.h"

void initiateRook(Enemy *rook, Vector2 position){
    rook->texture = LoadTexture("./textures/inimigo/torre.png");
    rook->rectangle.x = position.x;
    rook->initialPosition.x = rook->rectangle.x;

    rook->rectangle.y = position.y;
    rook->initialPosition.y = rook->rectangle.y;

    rook->rectangle.width = 20;
    rook->rectangle.height = 42;
    rook->direction = 1;
    rook->speed = 200;
    rook->type = 't';
    rook->color = WHITE;
    rook->isAlive = 1;
}

void hitRook(Enemy *rook, Player *player, Audio *audio){
    if(player->position.x + player->frame.width >= rook->rectangle.x &&
        player->position.x <= rook->rectangle.x + rook->rectangle.width &&
        player->position.y >= rook->rectangle.y){

        if(player->position.y - rook->rectangle.y < 5){
            rook->isAlive = 0;
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