#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float x, y;           // Kamera pozíciója
    float width, height;  // Kamera mérete
    float zoom;           // Zoom faktor
} Camera;

// Kamera inicializálása
void init_camera(Camera *camera, float x, float y, float width, float height);

// Kamera elmozdítása
void move_camera(Camera *camera, float dx, float dy);

// Kamera pozíciójának lekérése
void get_camera_position(const Camera *camera, float *x, float *y);

// Kamera méretének lekérése
void get_camera_size(const Camera *camera, float *width, float *height);

// Zoom beállítása
void set_camera_zoom(Camera *camera, float zoom);

// Zoom lekérdezése
float get_camera_zoom(const Camera *camera);

#endif // CAMERA_H
