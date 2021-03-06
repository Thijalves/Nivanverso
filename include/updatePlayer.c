#include "updatePlayer.h"
#include "audio.h"
#include "stdio.h"

//Funcao pra atualizar as variaveis do player
void updatePlayer(Player *player, float deltaTime, EnvItem *envItems, int envItemsLength, Platforms *platform, int platformsLength, Audio *audio){

    int hitFloor = 0;
    int hitWall = 0; // -1=esquerda e 1=direita

    //verifica as colisoes com cada obstaculo
    for (int i = 0; i < envItemsLength; i++){
        if (envItems[i].rect.x <= player->position.x + 15 &&
            envItems[i].rect.x + envItems[i].rect.width - 10 >= player->position.x &&
            envItems[i].rect.y >= player->position.y && 
            envItems[i].rect.y < player->position.y + player->vSpeed*deltaTime){
                hitFloor = 1;
                if(i == 1775)
                    player->vSpeed = -player->jumpS*1.3;
                else
                    player->vSpeed = 0.0f;
                player->position.y = envItems[i].rect.y;
                if(envItems[i].isLava){
                    //mata o player
                    player->vida--;
                    if(player->vida != 0) PlaySound(audio->damage);
                    player->color = RED;
                    player->vSpeed = -player->jumpS/2;
                    player->playerState = 4;
                }
            }
        
        //detecta colosioes laterais
        if (envItems[i].rect.y < player->position.y && //se o topo do obstaculo esta acima do p
            (player->position.y - player->frame.height) < envItems[i].rect.y + envItems[i].rect.height && //se o pe do obstaculo esta acima do p
            player->position.x > envItems[i].rect.x && //se o obstaculo esta a esquerda do p
            player->position.x - (envItems[i].rect.x + envItems[i].rect.width) < 1){ // se a diferenca entre o x do p e do obstaculo e < 3
            hitWall = -1; 
            //printf(" Tem uma parede na esquerda ");
        }
        if (envItems[i].rect.y < player->position.y &&
            (player->position.y - player->frame.height) < envItems[i].rect.y + envItems[i].rect.height &&
            player->position.x < envItems[i].rect.x &&
            envItems[i].rect.x - (player->position.x + player->frame.width) < 1){
            hitWall = 1; 
                //printf("Tem uma parede na direita");
        }
    
    }

    // verifica as colisoes com plataforma flutuante 
    for (int i = 0; i < platformsLength; i++){
        //detecta colosioes laterais
        if (platform[i].rectangle.y < player->position.y && //se o topo do obstaculo esta acima do p
            (player->position.y - player->frame.height) < platform[i].rectangle.y + platform[i].rectangle.height && //se o pe do obstaculo esta acima do p
            player->position.x > platform[i].rectangle.x && //se o obstaculo esta a esquerda do p
            player->position.x - (platform[i].rectangle.x + platform[i].rectangle.width) < 1){ // se a diferenca entre o x do p e do obstaculo e < 3
            hitWall = -1;
            if(player->facingDirection != platform[i].direction)
                player->position.x += (platform[i].speed/18) * platform[i].direction;
            //printf(" Tem uma parede na esquerda ");
        }
        if (platform[i].rectangle.y < player->position.y &&
            (player->position.y - player->frame.height) < platform[i].rectangle.y + platform[i].rectangle.height &&
            player->position.x < platform[i].rectangle.x &&
            platform[i].rectangle.x - (player->position.x + player->frame.width) < 1){
            hitWall = 1;
            if(player->facingDirection != platform[i].direction)
                player->position.x += (platform[i].speed/18) * platform[i].direction;
            //printf("Tem uma parede na direita");
        }
    
    }

    //atualiza o estado de animacao e o movimento horizonal
    if(IsKeyDown(KEY_D) && hitWall != 1 && player->playerState != 4){
        player->facingDirection = 1;
        player->position.x += player->hSpeed*deltaTime;
        player->playerState = 1;
        player->frame.width = (float)player->run.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->run.texture.height;
    }else if(IsKeyDown(KEY_A) && hitWall != -1 && player->playerState != 4){
        player->facingDirection = 0;
        player->position.x -= player->hSpeed*deltaTime;
        player->playerState = 1;
        player->frame.width = (float)player->runLeft.texture.width/player->run.maxFrames;
        player->frame.height = (float)player->runLeft.texture.height;
    }else if(player->playerState != 4){
        player->playerState = 0;
        player->frame.width = (float)player->idle.texture.width/player->idle.maxFrames;
        player->frame.height = (float)player->idle.texture.height;
    }

    //detecta pulo
    if (IsKeyDown(KEY_SPACE) && player->canJump && player->playerState != 4){
        player->vSpeed = -player->jumpS;
        player->canJump = false;
        PlaySound(audio->jump);
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