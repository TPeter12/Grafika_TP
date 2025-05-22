#ifndef TILEMAP_H
#define TILEMAP_H

#define MAP_WIDTH 50
#define MAP_HEIGHT 40
#define TILE_SIZE 40

extern int tilemap[MAP_HEIGHT][MAP_WIDTH];

void init_tilemap(void);
int pixel_to_tile_x(int pixelX);
int pixel_to_tile_y(int pixelY);
int tile_to_pixel_x(int tileX);
int tile_to_pixel_y(int tileY);
int is_tile_occupied(int x, int y);
void set_tile_occupied(int x, int y, int value);

#endif
