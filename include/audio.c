#include "audio.h"

void initiateAudio(Audio *audio){
    audio->menu = LoadMusicStream("audio/menu.mp3");
    audio->game = LoadMusicStream("audio/game.mp3");
    audio->jump = LoadSound("audio/jump.mp3");
    audio->damage = LoadSound("audio/damage.mp3");    
    audio->select = LoadSound("audio/selection.mp3");
    
}