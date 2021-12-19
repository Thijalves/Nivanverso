#include "audio.h"

void initiateAudio(Audio *audio){
    audio->menu = LoadMusicStream("audio/menu.mp3");
    audio->game = LoadMusicStream("audio/game.mp3");
    audio->jump = LoadSound("audio/jump.mp3");
    audio->damage = LoadSound("audio/damage.mp3");    
    audio->select = LoadSound("audio/selection.mp3");
    audio->enemyDeath = LoadSound("audio/killEnemy.mp3");    
}

void UnloadAudio(Audio *audio){
    UnloadMusicStream(audio->menu);
    UnloadMusicStream(audio->game);
    UnloadSound(audio->jump);
    UnloadSound(audio->damage);
    UnloadSound(audio->select);
    UnloadSound(audio->enemyDeath);
}