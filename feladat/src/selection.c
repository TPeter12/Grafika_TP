#include "selection.h"

void initSelection(Selection* selection) {
    selection->box.x = 0;
    selection->box.y = 0;
    selection->box.w = 0;
    selection->box.h = 0;
    selection->isSelecting = 0;
    selection->startX = 0;
    selection->startY = 0;
}

void updateSelection(Selection* selection, SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        selection->isSelecting = 1;
        selection->startX = e->button.x;
        selection->startY = e->button.y;
        selection->box.x = selection->startX;
        selection->box.y = selection->startY;
        selection->box.w = 0;
        selection->box.h = 0;
    }

    if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT) {
        selection->isSelecting = 0;
    }

    if (e->type == SDL_MOUSEMOTION && selection->isSelecting) {
        int currentX = e->motion.x;
        int currentY = e->motion.y;

        selection->box.w = currentX - selection->startX;
        selection->box.h = currentY - selection->startY;

        if (selection->box.w < 0) {
            selection->box.x = currentX;
            selection->box.w = -selection->box.w;
        }

        if (selection->box.h < 0) {
            selection->box.y = currentY;
            selection->box.h = -selection->box.h;
        }
    }
}

void renderSelection(SDL_Renderer* renderer, Selection* selection) {
    if (selection->isSelecting) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 144, 238, 144, 64); // Halvány zöld belső
        SDL_RenderFillRect(renderer, &selection->box);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Zöld keret
        SDL_RenderDrawRect(renderer, &selection->box);
    }
}
