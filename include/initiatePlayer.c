#include "initiatePlayer.h"

void initiatePlayer(Player *player){
    player->color = WHITE;
    player->hSpeed = 500; //era 125
    player->vSpeed = 0;
    player->jumpS = 250;
    player->idle.texture = LoadTexture("./textures/idle.png");
    player->idle.maxFrames = 12;
    player->position.x = 10;
    player->position.y = 256;
    player->frame.x = 0.0f;
    player->frame.y = 0.0f;
    player->facingDirection = 1;
    player->frame.width = (float)player->idle.texture.width/player->idle.maxFrames;
    player->frame.height = (float)player->idle.texture.height;
    player->vida = 3;
    
    //carrega a anumacao run
    player->run.texture = LoadTexture("./textures/run.png");
    player->run.maxFrames = 8;

    //animacao de correr para a esquerda
    player->runLeft.texture = LoadTexture("./textures/runLeft.png");
    player->runLeft.maxFrames = 8;

    //sprite pulando
    player->jumping.texture = LoadTexture("./textures/jumping.png");
    player->jumping.maxFrames = 1;

    //sprite caindo
    player->falling.texture = LoadTexture("./textures/falling.png");
    player->falling.maxFrames = 1;
}