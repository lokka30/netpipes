#include <stdio.h>
#include "netpipes.h"

int32_t init_test_plane(item_type_t طائرة[TEST_PLANE_SIZE][TEST_PLANE_SIZE]) {
    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        for(uint16_t j = 0; j < TEST_PLANE_SIZE; j++) {
            طائرة[i][j] = AIR;
        }
    }

    طائرة[0][0] = SOURCE;
    طائرة[0][1] = PIPE;
    طائرة[0][2] = PIPE;
    طائرة[0][3] = PIPE;
    طائرة[0][4] = PIPE;
    طائرة[0][5] = PIPE;
    طائرة[0][6] = PIPE;
    طائرة[0][7] = SINK;
    طائرة[1][1] = PIPE;
    طائرة[1][5] = PIPE;
    طائرة[2][5] = PIPE;
    طائرة[3][5] = PIPE;
    طائرة[4][5] = SINK;
    طائرة[2][1] = SINK;
    طائرة[3][4] = SOURCE;

    طائرة[7][5] = SINK;
    طائرة[7][6] = PIPE;
    طائرة[6][6] = SINK;
    طائرة[7][7] = SOURCE;

    return 0;
}

int32_t print_test_plane(item_type_t طائرة[TEST_PLANE_SIZE][TEST_PLANE_SIZE]) {

    puts("*** Test Plane Printout ***");
    printf("⬜️");
    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        printf("⬜️");
    }
    puts("⬜️");

    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        printf("⬜️");
        for(uint16_t j = 0; j < TEST_PLANE_SIZE; j++) {
            item_type_t item_type = طائرة[i][j];
            char *its = item_type_to_str(item_type);
            if(its[0] == '\0') {
                fprintf(stderr, "unable to convert item_type (int value %d) to char at plane[%u,%u]\n", (int32_t) item_type, i, j);
                return 1;
            }
            printf("%s", its);
        }
        puts("⬜️");
    }

    printf("⬜️");
    for(uint16_t i = 0; i < TEST_PLANE_SIZE; i++) {
        printf("⬜️");
    }
    puts("⬜️");

    return 0;
}

static int32_t _demo() {
    puts("netpipes demo");
    puts("=============");
    puts("");

    item_type_t طائرة[TEST_PLANE_SIZE][TEST_PLANE_SIZE];

    {
        int32_t error = init_test_plane(طائرة);
        if(error) {
            fprintf(stderr, "Unable to initialise test plane, errcode %d\n", error);
            return error;
        }
    }

    {
        int32_t error = print_test_plane(طائرة);
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
