#include <stdio.h>
#include <stdint.h>

#include "netpipes.h"


const uint16_t TEST_PLANE_SIZE = 8;

static int32_t _init_test_plane(item_type_t plane[TEST_PLANE_SIZE][TEST_PLANE_SIZE]) {
    // Set all items to AIR.
    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        for(uint16_t j = 0; j < TEST_PLANE_SIZE; j++) {
            plane[i][j] = AIR;
        }
    }

    // Manually build test environment.
    plane[0][0] = SOURCE;
    plane[0][1] = PIPE;
    plane[0][2] = PIPE;
    plane[0][3] = SINK;
    plane[1][1] = PIPE;
    plane[2][1] = SINK;

    return 0;
}

static int32_t _print_test_plane(item_type_t plane[TEST_PLANE_SIZE][TEST_PLANE_SIZE]) {

    puts("*** Test Plane Printout ***");
    putchar('+');
    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        putchar('-');
    }
    puts("+");

    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        putchar('|');
        for(uint16_t j = 0; j < TEST_PLANE_SIZE; j++) {
            item_type_t item_type = plane[i][j];
            char c = item_type_to_char(item_type);
            if(c == '\0') {
                fprintf(stderr, "unable to convert item_type (int value %d) to char at plane[%u,%u]\n", (int32_t) item_type, i, j);
                return 1;
            }
            putchar(c);
        }
        puts("|");
    }

    putchar('+');
    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        putchar('-');
    }
    puts("+");

    return 0;
}

static int32_t _demo() {
    puts("netpipes demo");
    puts("=============");
    puts("");

    item_type_t plane[TEST_PLANE_SIZE][TEST_PLANE_SIZE];

    {
        int32_t error = _init_test_plane(plane);
        if(error) {
            fprintf(stderr, "Unable to initialise test plane, errcode %d\n", error);
            return error;
        }
    }

    {
        int32_t error = _print_test_plane(plane);
        if(error) {
            fprintf(stderr, "Unable to print test plane, errcode %d\n", error);
            return error;
        }
    }

    puts("\nOk");
    return 0;
}

int32_t main() {
    int32_t error = _demo();
    if(error) {
        puts("\n+===============+");
        printf("| MALFUNCTION %d |\n", error);
        puts("+===============+");
    }
    return error;
}

