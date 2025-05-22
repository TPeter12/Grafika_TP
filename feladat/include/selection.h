#ifndef SELECTION_H
#define SELECTION_H

#include <SDL2/SDL.h>
#include <stdbool.h>

void start_selection(int worldX, int worldY);
void update_selection(int worldX, int worldY);
void finish_selection(void);
void draw_selection(SDL_Renderer* renderer, int cameraX, int cameraY);
bool is_selecting(void);

#endif
