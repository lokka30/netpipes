#include <stdint.h>

typedef enum ItemType {
    AIR = 0,
    PIPE = 1,
    SOURCE = 2,
    SINK = 3
} item_type_t;

char item_type_to_char(item_type_t item_type) {
    switch(item_type) {
        case AIR:
            return ':'; // visually different enough to the rest of the chars
        case PIPE:
            return '='; // it looks like a pipe, no?
        case SOURCE:
            return 'O'; // as in 'out'...
        case SINK:
            return 'I'; // as in 'in'...
        default:
            return '\0';
    }
}

char* item_type_to_str(item_type_t item_type) {
    switch(item_type) {
        case AIR:
            return "Air";
        case SOURCE:
            return "Source";
        case SINK:
            return "Sink";
        default:
            return NULL;
    }
}

typedef struct Coord2D {
    int64_t x;
    int64_t y;
} coord2d_t;

typedef struct Coord3D {
    int64_t x;
    int64_t y;
    int64_t z;
} coord3d_t;



