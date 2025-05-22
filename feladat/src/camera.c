#include "camera.h"
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define EDGE_SCROLL_MARGIN 20
#define CAMERA_SPEED 5

static int cameraX = 0;
static int cameraY = 0;

void init_camera(void) {
    cameraX = 0;
    cameraY = 0;
}

void update_camera(int mouseX, int mouseY) {
    if (mouseX < EDGE_SCROLL_MARGIN) cameraX -= CAMERA_SPEED;
    if (mouseX > SCREEN_WIDTH - EDGE_SCROLL_MARGIN) cameraX += CAMERA_SPEED;
    if (mouseY < EDGE_SCROLL_MARGIN) cameraY -= CAMERA_SPEED;
    if (mouseY > SCREEN_HEIGHT - EDGE_SCROLL_MARGIN) cameraY += CAMERA_SPEED;
}

int get_camera_x(void) {
    return cameraX;
}

int get_camera_y(void) {
    return cameraY;
}
