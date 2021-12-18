#include "clouds.h"
#include "raylib.h"

void generateClouds(Clouds *clouds){
    int posX = GetRandomValue(-50, 8000);
    int posY = GetRandomValue(0, 150);

    clouds->speed = 5;
    clouds->direction = 1;
    clouds->position = (Vector2){(float)posX, (float)posY};
}