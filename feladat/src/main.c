#include <SDL2/SDL.h>
#include <stdbool.h>
#include "unit.h"
#include "selection.h"
#include "tilemap.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define EDGE_SCROLL_MARGIN 20
#define CAMERA_SPEED 10

void draw_tilemap_grid(SDL_Renderer* renderer, int cameraX, int cameraY) {
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);

    for (int y = 0; y <= MAP_HEIGHT; y++) {
        int yPos = y * TILE_SIZE - cameraY;
        SDL_RenderDrawLine(renderer, -cameraX, yPos, MAP_WIDTH * TILE_SIZE - cameraX, yPos);
    }

    for (int x = 0; x <= MAP_WIDTH; x++) {
        int xPos = x * TILE_SIZE - cameraX;
        SDL_RenderDrawLine(renderer, xPos, -cameraY, xPos, MAP_HEIGHT * TILE_SIZE - cameraY);
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("RTS_TESTER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Egérkurzor fogása az ablakon belülre
    SDL_SetWindowGrab(window, SDL_TRUE);
    SDL_ShowCursor(SDL_ENABLE);

    init_tilemap();
    init_units();

    int cameraX = 0;
    int cameraY = 0;

    bool running = true;
    SDL_Event event;

    while (running) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Az egér ne tudjon kimenni az ablakból, korlátozás:
        if (mouseX < 0) mouseX = 0;
        if (mouseX > SCREEN_WIDTH) mouseX = SCREEN_WIDTH;
        if (mouseY < 0) mouseY = 0;
        if (mouseY > SCREEN_HEIGHT) mouseY = SCREEN_HEIGHT;

        // Kamera mozgatás az egér szélénél
        if (mouseX < EDGE_SCROLL_MARGIN) cameraX -= CAMERA_SPEED;
        if (mouseX > SCREEN_WIDTH - EDGE_SCROLL_MARGIN) cameraX += CAMERA_SPEED;
        if (mouseY < EDGE_SCROLL_MARGIN) cameraY -= CAMERA_SPEED;
        if (mouseY > SCREEN_HEIGHT - EDGE_SCROLL_MARGIN) cameraY += CAMERA_SPEED;

        // Kamera korlátok
        if (cameraX < 0) cameraX = 0;
        if (cameraY < 0) cameraY = 0;
        int maxCameraX = MAP_WIDTH * TILE_SIZE - SCREEN_WIDTH;
        int maxCameraY = MAP_HEIGHT * TILE_SIZE - SCREEN_HEIGHT;
        if (cameraX > maxCameraX) cameraX = maxCameraX;
        if (cameraY > maxCameraY) cameraY = maxCameraY;

        // Egér világ koordináta (kamera eltolással)
        int worldMouseX = mouseX + cameraX;
        int worldMouseY = mouseY + cameraY;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        start_selection(worldMouseX, worldMouseY);
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        int tileX = pixel_to_tile_x(worldMouseX);
                        int tileY = pixel_to_tile_y(worldMouseY);

                        if (!is_tile_occupied(tileX, tileY)) {
                            for (int i = 0; i < numUnits; i++) {
                                if (units[i].selected) {
                                    units[i].targetX = tile_to_pixel_x(tileX) + TILE_SIZE / 2;
                                    units[i].targetY = tile_to_pixel_y(tileY) + TILE_SIZE / 2;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        finish_selection();
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (is_selecting()) {
                        update_selection(worldMouseX, worldMouseY);
                    }
                    break;
            }
        }

        update_units();

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        draw_tilemap_grid(renderer, cameraX, cameraY);
        draw_units(renderer, cameraX, cameraY);
        draw_selection(renderer, cameraX, cameraY);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
