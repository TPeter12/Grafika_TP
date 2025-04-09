#include "render.h"

void render_isometric(SDL_Renderer* renderer, int x, int y, int tile_width, int tile_height, Camera* camera) {
    float zoom = get_camera_zoom(camera);

    // Izometrikus koordináták kiszámítása, figyelembe véve a zoom-ot
    int scaled_tile_width = tile_width * zoom;
    int scaled_tile_height = tile_height * zoom;

    int px = ((x - y) * scaled_tile_width / 2) + camera->width / 2 - camera->x;
    int py = ((x + y) * scaled_tile_height / 2) - camera->y;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Fehér szín

    SDL_Rect rect = {
        px,
        py,
        scaled_tile_width,
        scaled_tile_height
    };

    SDL_RenderDrawRect(renderer, &rect);  // Csak a körvonalat rajzoljuk ki
}
