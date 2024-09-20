#include <stdint.h>

typedef enum ItemType {
    AIR = 0,
    PIPE = 1,
    SOURCE = 2,
    SINK = 3
} item_type_t;

/*
   .PURPOSE
   Returns a character representation of an Item Type.

   .RETURNS
   Character representation of item type.

   .ERROR HANDLING
   Returns null character if an item type value is not handled.
*/
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

/*
   .PURPOSE
   Returns an English string name of a provided Item Type.

   .RETURNS
   Name representation of Item Type.

   .ERROR HANDLING
   Returns NULL if an Item Type does not have a switch branch defined.
   */
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



