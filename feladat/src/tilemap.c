#include "tilemap.h"

int tilemap[MAP_HEIGHT][MAP_WIDTH];

void init_tilemap(void) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            tilemap[y][x] = 0;  // minden tile szabad
        }
    }
}

int pixel_to_tile_x(int pixelX) {
    return pixelX / TILE_SIZE;
}

int pixel_to_tile_y(int pixelY) {
    return pixelY / TILE_SIZE;
}

int tile_to_pixel_x(int tileX) {
    return tileX * TILE_SIZE;
}

int tile_to_pixel_y(int tileY) {
    return tileY * TILE_SIZE;
}

int is_tile_occupied(int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return 1;
    return tilemap[y][x] == 1;
}

void set_tile_occupied(int x, int y, int value) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return;
    tilemap[y][x] = value;
}
