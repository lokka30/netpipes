#include <stdlib.h>
#include "items.h"

char* item_type_to_str(item_type_t item_type) {
    switch(item_type) {
        case AIR:
            return ".";
        case PIPE:
            return "-";
        case SOURCE:
            return "+";
        case SINK:
            return "*";
        default:
            return "?";
    }
}

char* item_type_to_name(item_type_t item_type) {
    switch(item_type) {
        case AIR:
            return "Air";
        case SOURCE:
            return "Source";
        case SINK:
            return "Sink";
        case PIPE:
            return "Pipe";
        default:
            return "?";
    }
}

item_t air_item() {
    item_t item = {
        .type = AIR,
        .net_id = 0u,
    };
    return item;
}

int32_t init_iplane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
) {
    for(uint8_t i = 0u; i < xlen; i++) {
        for(uint8_t j = 0u; j < ylen; j++) {
            iplane[i][j] = air_item();
        }
    }
    return 0;
}
