#ifndef SELECTION_H
#define SELECTION_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect box;
    int isSelecting;
    int startX, startY;
} Selection;

void initSelection(Selection* selection);
void updateSelection(Selection* selection, SDL_Event* e);
void renderSelection(SDL_Renderer* renderer, Selection* selection);

#endif // SELECTION_H
