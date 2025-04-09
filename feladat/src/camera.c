#include "camera.h"
#include <stddef.h>  // NULL makró használatához

// Kamera inicializálása
void init_camera(Camera *camera, float x, float y, float width, float height) {
    camera->x = x;
    camera->y = y;
    camera->width = width;
    camera->height = height;
    camera->zoom = 1.0f;
}

// Kamera elmozdítása
void move_camera(Camera *camera, float dx, float dy) {
    camera->x += dx;
    camera->y += dy;
}

// Kamera pozíciójának lekérése
void get_camera_position(const Camera *camera, float *x, float *y) {
    if (x != NULL) *x = camera->x;
    if (y != NULL) *y = camera->y;
}

// Kamera méretének lekérése
void get_camera_size(const Camera *camera, float *width, float *height) {
    if (width != NULL) *width = camera->width;
    if (height != NULL) *height = camera->height;
}

// Zoom beállítása
void set_camera_zoom(Camera *camera, float zoom) {
    if (zoom < 0.1f) zoom = 0.1f;   // Alsó határ
    if (zoom > 5.0f) zoom = 5.0f;   // Felső határ
    camera->zoom = zoom;
}

// Zoom lekérdezése
float get_camera_zoom(const Camera *camera) {
    return camera->zoom;
}
