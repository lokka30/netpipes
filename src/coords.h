#ifndef COORDS_H
#define COORDS_H

#include <stdint.h>

typedef struct Coord2D {
    int64_t x;
    int64_t y;
} coord2d_t;

typedef struct Coord3D {
    int64_t x;
    int64_t y;
    int64_t z;
} coord3d_t;

#endif
