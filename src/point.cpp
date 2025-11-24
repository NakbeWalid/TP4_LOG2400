#include "point.h"
#include <stdio.h>

void afficher_point(Point p) {
    printf("Point : (%f, %f, %f)\n", p.x, p.y, p.z);
}

void deplacer_point(Point* p, float dx, float dy, float dz) {
    p->x += dx;
    p->y += dy;
    p->z += dz;
}
