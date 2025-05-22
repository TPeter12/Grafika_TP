#include "unit.h"
#include "tilemap.h"
#include <SDL2/SDL.h>
#include <math.h>

Unit units[MAX_UNITS];
int numUnits = MAX_UNITS;

void init_units(void) {
    for (int i = 0; i < MAX_UNITS; i++) {
        int tileX = i % MAP_WIDTH;
        int tileY = i / MAP_WIDTH;
        units[i].x = tile_to_pixel_x(tileX) + TILE_SIZE / 2;
        units[i].y = tile_to_pixel_y(tileY) + TILE_SIZE / 2;
        units[i].targetX = units[i].x;
        units[i].targetY = units[i].y;
        units[i].selected = false;

        set_tile_occupied(tileX, tileY, 1);  // tile foglaltság jelzése
    }
}

void update_units(void) {
    for (int i = 0; i < numUnits; i++) {
        if (units[i].selected) {
            float dx = units[i].targetX - units[i].x;
            float dy = units[i].targetY - units[i].y;

            if (fabsf(dx) < 1.0f && fabsf(dy) < 1.0f) {
                units[i].x = units[i].targetX;
                units[i].y = units[i].targetY;
                continue;
            }

            int stepX = 0;
            int stepY = 0;

            if (dx > 0) stepX = TILE_SIZE;
            else if (dx < 0) stepX = -TILE_SIZE;

            if (dy > 0) stepY = TILE_SIZE;
            else if (dy < 0) stepY = -TILE_SIZE;

            float newX = units[i].x + stepX;
            float newY = units[i].y + stepY;

            int tileX = pixel_to_tile_x(newX);
            int tileY = pixel_to_tile_y(newY);

            int oldTileX = pixel_to_tile_x(units[i].x);
            int oldTileY = pixel_to_tile_y(units[i].y);

            if (!is_tile_occupied(tileX, tileY) || (tileX == oldTileX && tileY == oldTileY)) {
                set_tile_occupied(oldTileX, oldTileY, 0);
                set_tile_occupied(tileX, tileY, 1);

                units[i].x = newX;
                units[i].y = newY;
            }
            // ha foglalt, nem lépünk
        }
    }
}

bool unit_in_rect(Unit* u, SDL_Rect* rect) {
    int x = (int)u->x;
    int y = (int)u->y;
    return (x > rect->x && x < rect->x + rect->w &&
            y > rect->y && y < rect->y + rect->h);
}

void draw_units(SDL_Renderer* renderer, int cameraX, int cameraY) {
    for (int i = 0; i < numUnits; i++) {
        SDL_Rect r = {
            (int)(units[i].x - cameraX) - 10,
            (int)(units[i].y - cameraY) - 10,
            20, 20
        };
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &r);

        if (units[i].selected) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_Rect bar = { r.x, r.y - 7, r.w, 5 };
            SDL_RenderFillRect(renderer, &bar);
        }
    }
}
