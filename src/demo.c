#include "demo.h"

int32_t print_plane_item_types(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
) {
    for(uint32_t xpos = 0; xpos < xlen; xpos++) {
        for(uint32_t ypos = 0; ypos < ylen; ypos++) {
            item_t item = iplane[xpos][ypos];

            char network_color[11] = { '\0' };
            network_color_to_str(item.net_id, network_color);

            printf(
                "%s%s%s   ",
                item.type == AIR ? LIGHT_GRAY : network_color,
                item_type_to_str(item.type),
                LIGHT_WHITE
            );
        }
        puts("");
    }
    return 0;
}

int32_t print_plane_network_ids(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
) {
    for(uint32_t xpos = 0; xpos < xlen; xpos++) {
        for(uint32_t ypos = 0; ypos < ylen; ypos++) {
            item_t item = iplane[xpos][ypos];

            char network_color[11] = { '\0' };
            network_color_to_str(item.net_id, network_color);

            printf(
                "%s%-3hhu%s ",
                item.net_id == 0 ? LIGHT_GRAY : network_color,
                item.net_id,
                LIGHT_WHITE
            );
        }
        puts("");
    }
    return 0;
}

int32_t print_plane_adjacently(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
) {
    for(uint32_t xpos = 0; xpos < xlen; xpos++) {
        for(uint32_t ypos = 0; ypos < ylen; ypos++) {
            item_t item = iplane[xpos][ypos];

            char network_color[11] = { '\0' };
            network_color_to_str(item.net_id, network_color);

            printf(
                "%s%s%s   ",
                item.type == AIR ? LIGHT_GRAY : network_color,
                item_type_to_str(item.type),
                LIGHT_WHITE
            );
        }
        puts("");
        for(uint32_t ypos = 0; ypos < ylen; ypos++) {
            item_t item = iplane[xpos][ypos];

            wchar_t net_id_str[PLANE_SIZE];
            wchar_t net_id_super[PLANE_SIZE];
            swprintf(net_id_str, sizeof(net_id_str) / sizeof(wchar_t), L"%hhu", item.net_id);
            to_superscript_wchar(net_id_str, net_id_super);

            char network_color[11] = { '\0' };
            network_color_to_str(item.net_id, network_color);

            wprintf(
                L" %s%-2ls%s ",
                item.net_id == 0 ? LIGHT_GRAY : network_color,
                net_id_super,
                LIGHT_WHITE
            );
        }
        puts("");
    }
    return 0;
}

int32_t demo() {
    printf(
        "%snetpipes demo%s\n====================\n%s",
        LIGHT_GREEN,
        LIGHT_GRAY,
        LIGHT_WHITE
    );

    int32_t error = 0;
    item_t iplane[PLANE_SIZE][PLANE_SIZE];

    puts("Initializing test plane...");
    init_test_plane(iplane, PLANE_SIZE, PLANE_SIZE);
    
    puts("Networkinating test plane...");
    networkinate_plane(iplane);

    // Show Item Types
    printf("%s\nItem Types:\n", LIGHT_WHITE);
    if((error = print_plane_item_types(iplane, PLANE_SIZE, PLANE_SIZE))) {
        return error;
    }

    // Show Network IDs
    printf("%s\nNetwork IDs:\n", LIGHT_WHITE);
    if((error = print_plane_network_ids(iplane, PLANE_SIZE, PLANE_SIZE))) {
        return error;
    }

    // Show Adjacent Planes (items types with network IDs in same printout)
    printf("%s\nAdjacent Planes:\n", LIGHT_WHITE);
    if((error = print_plane_adjacently(iplane, PLANE_SIZE, PLANE_SIZE))) {
        return error;
    }

    printf("%s\nOk\n", LIGHT_WHITE);

    return error;
}

int32_t init_test_plane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen
) {
    #define ROWS 8
    #define COLUMNS 8

    if(xlen < ROWS || ylen < COLUMNS) {
        return 1;
    }

    // character representations of the item types to fill the item plane
    char repr_test_plane[ROWS][COLUMNS] = {
        {'+', '-', '-', ' ', '-', '-', '-', '*'},
        {'-', ' ', '*', ' ', '+', ' ', '-', ' '},
        {'*', ' ', ' ', ' ', ' ', ' ', '-', '*'},
        {' ', '*', '-', '+', '-', '*', ' ', ' '},
        {'+', ' ', '-', ' ', '*', ' ', '*', ' '},
        {'-', ' ', '*', ' ', ' ', ' ', '-', '*'},
        {'-', '*', ' ', '-', '*', ' ', '-', ' '},
        {'-', '*', ' ', '+', '-', '-', '-', '+'},
    };

    for(uint32_t xpos = 0u; xpos < xlen; xpos++) {
        for(uint32_t ypos = 0u; ypos < ylen; ypos++) {
            if(xpos >= ROWS || ypos >= COLUMNS) {
                iplane[xpos][ypos] = air_item();
                continue;
            }

            char repr_c = repr_test_plane[xpos][ypos];
            item_type_t item_type;

            switch(repr_c) {
                case '+':
                    item_type = SOURCE;
                    break;
                case '-':
                    item_type = PIPE;
                    break;
                case '*':
                    item_type = SINK;
                    break;
                case ' ':
                    item_type = AIR;
                    break;
                default:
                    return 1;
            }

            item_t item = {
                .type = item_type,
                .net_id = 0u,
            };

            iplane[xpos][ypos] = item;
        }
    }

    return 0;
}
