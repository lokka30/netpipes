#ifndef ITEMS_H
#define ITEMS_H

typedef enum ItemType {
    AIR = 0,
    PIPE = 1,
    SOURCE = 2,
    SINK = 3,
    
    DEBUG = 64 // Debug cell with this value
} item_type_t;

char* item_type_to_str(item_type_t item_type);

char* item_type_to_name(item_type_t item_type);

#endif
