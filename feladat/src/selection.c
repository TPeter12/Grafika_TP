#include "selection.h"
#include "unit.h"

static SDL_Rect selectionBox;
static int startX, startY;
static bool selecting = false;

void start_selection(int worldX, int worldY) {
    selecting = true;
    startX = worldX;
    startY = worldY;
    selectionBox.x = startX;
    selectionBox.y = startY;
    selectionBox.w = 0;
    selectionBox.h = 0;
}

void update_selection(int worldX, int worldY) {
    if (selecting) {
        selectionBox.w = worldX - startX;
        selectionBox.h = worldY - startY;
        selectionBox.x = startX;
        selectionBox.y = startY;
    }
}

void finish_selection(void) {
    if (!selecting) return;
    selecting = false;

    SDL_Rect sel = selectionBox;
    if (sel.w < 0) { sel.x += sel.w; sel.w = -sel.w; }
    if (sel.h < 0) { sel.y += sel.h; sel.h = -sel.h; }

    for (int i = 0; i < numUnits; i++) {
        units[i].selected = unit_in_rect(&units[i], &sel);
    }
}

void draw_selection(SDL_Renderer* renderer, int cameraX, int cameraY) {
    if (selecting) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_Rect r = {
            selectionBox.x - cameraX,
            selectionBox.y - cameraY,
            selectionBox.w,
            selectionBox.h
        };
        SDL_RenderDrawRect(renderer, &r);
    }
}

bool is_selecting(void) {
    return selecting;
}
