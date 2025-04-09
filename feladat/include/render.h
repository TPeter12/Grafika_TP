#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "camera.h"

// TileSize struktúra deklarálása
typedef struct {
    int width;
    int height;
} TileSize;

// Izometrikus térkép renderelése a kamera és zoom figyelembevételével
void render_isometric(SDL_Renderer* renderer, int x, int y, int tile_width, int tile_height, Camera* camera);

#endif // RENDER_H
