#ifndef NETWORKS_H
#define NETWORKS_H

#include <stdint.h>
#include "items.h"

int32_t _networkinate_item(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xpos,
    uint32_t ypos,
    uint32_t net_id
);

int32_t _networkinate_search(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xpos,
    uint32_t ypos,
    uint32_t net_id
);

int32_t networkinate_plane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE]
);

void network_color_to_str(
    uint32_t net_id,
    char str[11]
);

int64_t network_calc_balance(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t net_id
);

#endif