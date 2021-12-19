#include "knight.h"
             
void initiateKnight(Enemy *knight, Vector2 position){
    knight->texture = LoadTexture("./textures/inimigo/cavalo.png");
    knight->rectangle.height = 49;
    knight->rectangle.width = 25;
    knight->initialPosition = position;
    knight->isAlive = 1;
    knight->rectangle.x = knight->initialPosition.x;
    knight->rectangle.y = knight->initialPosition.y;
    knight->type = 'k';
    knight->jumpSpeed = 300;
    knight->speed = 350;

}

void hitKnight(Enemy *knight, Player *player, Audio *audio){
    if( player->position.x + player->frame.width >= knight->rectangle.x &&
        player->position.x <= knight->rectangle.x + knight->rectangle.width &&
        player->position.y >= knight->rectangle.y && player->position.y-player->frame.height <= knight->rectangle.y+knight->rectangle.height){

        if(player->position.y - knight->rectangle.y < 5){
            knight->isAlive = 0;
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