#include "updatePlayer.h"

//Funcao pra atualizar as variaveis do player
void updatePlayer(Player *player, float deltaTime, EnvItem *envItems, int envItemsLength){

    int hitFloor = 0;
    int hitWall = 0; // -1=esquerda e 1=direita
    
    //verifica as colisoes com cada obstaculo
    for (int i = 0; i < envItemsLength; i++){
        if (envItems[i].rect.x <= player->position.x + 15 &&
            envItems[i].rect.x + envItems[i].rect.width >= player->position.x &&
            envItems[i].rect.y >= player->position.y && 
            envItems[i].rect.y < player->position.y + player->vSpeed*deltaTime){
                hitFloor = 1;
                player->vSpeed = 0.0f;
                player->position.y = envItems[i].rect.y;
                if(envItems[i].isLava){
                    player->color = RED;
                    player->vSpeed = -player->jumpS/2;
                    
                }
            }
        
        //detecta colosioes laterais
        if (envItems[i].rect.y < player->position.y && //se o topo do obstaculo esta acima do p
            (player->position.y-player->frame.height)<envItems[i].rect.y+envItems[i].rect.height && //se o pe do obstaculo esta acima do p
            player->position.x > envItems[i].rect.x && //se o obstaculo esta a esquerda do p
            player->position.x-(envItems[i].rect.x+envItems[i].rect.width) < 1){ // se a diferenca entre o x do p e do obstaculo e < 3
            hitWall = -1; 
            //printf(" Tem uma parede na esquerda ");
        }
        if (envItems[i].rect.y < player->position.y &&
            (player->position.y-player->frame.height)<envItems[i].rect.y+envItems[i].rect.height &&
            player->position.x < envItems[i].rect.x &&
            envItems[i].rect.x-(player->position.x+player->frame.width) < 1){
            hitWall = 1; 
                //printf("Tem uma parede na direita");
        }
    
    }

    //atualiza o estado de animacao e o movimento horizonal
    if(IsKeyDown(KEY_D) && hitWall != 1){
        player->facingDirection = 1;
        player->position.x += player->hSpeed*deltaTime;
        player->playerState = 1;
        player->frame.width = (float)player->run.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->run.texture.height;
    }else if(IsKeyDown(KEY_A) && hitWall != -1){
        player->facingDirection = 0;
        player->position.x -= player->hSpeed*deltaTime;
        player->playerState = 1;
        player->frame.width = (float)player->runLeft.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->runLeft.texture.height;
    }else{
        player->playerState = 0;
        player->frame.width = (float)player->idle.texture.width/player->idle.maxFrames;
        player->frame.height = (float)player->idle.texture.height;
    }

    //detecta pulo
    if (IsKeyDown(KEY_SPACE) && player->canJump){
        player->vSpeed = -player->jumpS;
        player->canJump = false;
    }

    if (!hitFloor){
        //deixar a velocidade de queda maior que a de subida
        if(player->vSpeed >=0){
            player->position.y += player->vSpeed*deltaTime;
            player->vSpeed += gravity*deltaTime;
        }else{
            player->position.y += player->vSpeed*deltaTime;
            player->vSpeed += gravity*deltaTime*1.4;
        }
        

        if(player->vSpeed < 0){ //player esta subindo
            player->playerState = 2;
            player->frame.width = (float)player->jumping.texture.width;
            player->frame.height = (float)player->jumping.texture.height;
        }else if(player->vSpeed > 10){
            player->playerState = 3;
            player->frame.width = (float)player->falling.texture.width;
            player->frame.height = (float)player->falling.texture.height;
        }

        player->canJump = false;
    }else{
        player->canJump = true;
    }

}