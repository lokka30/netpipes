#ifndef DEMO_H
#define DEMO_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "networks.h"
#include "misc.h"

#define LIGHT_GREEN     "\033[1;32m"
#define LIGHT_WHITE     "\033[1;37m"
#define LIGHT_GRAY      "\033[0;37m"
#define DARK_GRAY       "\033[1;30m"

int32_t demo();

int32_t print_plane_item_types(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
);

int32_t print_plane_network_ids(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
);

int32_t print_plane_adjacently(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
);

int32_t init_test_plane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
);

#endif