#include <stdio.h>
#include <math.h>

typedef struct {
    double length; 
    double width;  
    double height; 
} Brick;

void set_size(Brick *c, double length, double width, double height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        printf("Hiba: Az élek hossza nem lehet nulla vagy negatív!\n");
        return;
    }
    c->length = length;
    c->width = width;
    c->height = height;
}

double calc_V(const Brick *c) {
    return c->length * c->width * c->height;
}

double calc_S(const Brick *c) {
    return 2 * (c->length * c->width + c->width * c->height + c->height * c->length);
}

int has_square_face(const Brick *brick) {
    return (brick->length == brick->width || brick->width == brick->height || brick->height == brick->length);
}

int main() {
    Brick brick;
   
    set_size(&brick, 5.0, 3.0, 5.0); 
    
    if (has_square_face(&brick)) {
        printf("A téglatestnek van négyzet alakú lapja.\n");
    } else {
        printf("A téglatestnek nincs négyzet alakú lapja.\n");
    }

    printf("A téglatest térfogata: %.2f köb egység\n", calc_V(&brick));
    printf("A téglatest felszíne: %.2f négyzet egység\n", calc_S(&brick));
    
    return 0;
}
