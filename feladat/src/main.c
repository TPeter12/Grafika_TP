#include <SDL2/SDL.h>
#include <stdbool.h>
#include "camera.h"
#include "render.h"
#include "selection.h"

#define SDL_MAIN_HANDLED

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Isometric Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;

    Camera camera;
    init_camera(&camera, 0, 0, 1280, 800);

    Selection selection;
    initSelection(&selection);

    TileSize tileSize = { 80, 64 };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }

            updateSelection(&selection, &e);

            if (e.type == SDL_MOUSEWHEEL) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                float zoomBefore = get_camera_zoom(&camera);
                float worldMouseX = (mouseX - camera.width / 2 + camera.x) / zoomBefore;
                float worldMouseY = (mouseY + camera.y) / zoomBefore;

                if (e.wheel.y > 0) {
                    set_camera_zoom(&camera, zoomBefore * 1.1f);
                } else if (e.wheel.y < 0) {
                    set_camera_zoom(&camera, zoomBefore / 1.1f);
                }

                float zoomAfter = get_camera_zoom(&camera);
                camera.x = worldMouseX * zoomAfter - (mouseX - camera.width / 2);
                camera.y = worldMouseY * zoomAfter - mouseY;
            }
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX < 20) move_camera(&camera, -7, 0);
        if (mouseX > 1260) move_camera(&camera, 7, 0);
        if (mouseY < 20) move_camera(&camera, 0, -7);
        if (mouseY > 780) move_camera(&camera, 0, 7);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int y = 0; y < 120; y++) {
            for (int x = 0; x < 120; x++) {
                render_isometric(renderer, x, y, tileSize.width, tileSize.height, &camera);
            }
        }

        renderSelection(renderer, &selection);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect cursorRect = { mouseX - 10, mouseY - 10, 20, 20 };
        SDL_RenderFillRect(renderer, &cursorRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
