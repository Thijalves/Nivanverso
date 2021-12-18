#include "floatingPlatform.h"   //inicializa a plataforma flutuante
    
void initiateFloatingPlatform(Platforms *platform, Vector2 position){    
    platform->texture = LoadTexture("./textures/tilemap/plataforma.png");
    platform->initialPosition = position;
    platform->direction = 1;
    platform->rectangle.width = 96;
    platform->rectangle.height = 32;
    platform->rectangle.x = platform->initialPosition.x;
    platform->rectangle.y = platform->initialPosition.y;
    platform->speed = 75;
}
