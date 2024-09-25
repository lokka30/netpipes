#ifndef ITEMS_H
#define ITEMS_H

#define PLANE_SIZE 8
#define PLANE_SIZE_SQR PLANE_SIZE * PLANE_SIZE
#define UNITS_PER_SOURCE 8

typedef enum ItemType {
    AIR = 0,
    PIPE = 1,
    SOURCE = 2,
    SINK = 3
} item_type_t;

char* item_type_to_str(item_type_t item_type);

char* item_type_to_name(item_type_t item_type);

typedef struct Item {
    item_type_t type;
    uint8_t     net_id;
} item_t;

item_t air_item();

int32_t init_iplane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
);

#endif
