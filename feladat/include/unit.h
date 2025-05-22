#ifndef UNIT_H
#define UNIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    float x, y;
    float targetX, targetY;
    bool selected;
} Unit;

#define MAX_UNITS 10

extern Unit units[MAX_UNITS];
extern int numUnits;

void init_units(void);
void update_units(void);
bool unit_in_rect(Unit* u, SDL_Rect* rect);
void draw_units(SDL_Renderer* renderer, int cameraX, int cameraY);

#endif
