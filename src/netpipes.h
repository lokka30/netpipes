#ifndef NETPIPES_H
#define NETPIPES_H

#include <stdint.h>
#include "items.h"
#include "coords.h"

#define TEST_PLANE_SIZE 8u

int32_t init_test_plane(item_type_t plane[TEST_PLANE_SIZE][TEST_PLANE_SIZE]);

int32_t print_test_plane(item_type_t plane[TEST_PLANE_SIZE][TEST_PLANE_SIZE]);

#endif
