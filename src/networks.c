#include <stdio.h>
#include <stdbool.h>
#include "networks.h"
#include "misc.h"

int32_t _networkinate_item(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xpos,
    uint32_t ypos,
    uint32_t net_id
) {
    int32_t error = 0;

    // ensure index not out of bounds
    if(xpos < 0 || xpos >= PLANE_SIZE || ypos < 0 || ypos >= PLANE_SIZE) {
        return 1;
    }

    // Item at the location in the iplane.
    item_t item = iplane[xpos][ypos];
    
    // If the item already has the current netid or it's air,
    // there's no point in exploring around this item; return.
    if (item.net_id == net_id || item.type == AIR) {
        return 0;
    }

    // Join this item to the current network.
    iplane[xpos][ypos].net_id = net_id;

    // Can we go north?
    if (xpos > 0) {
        if((error = _networkinate_item(iplane, xpos - 1, ypos, net_id))) {
            return error;
        }
    }

    // Can we go east?
    if (ypos + 1 < PLANE_SIZE) {
        if((error = _networkinate_item(iplane, xpos, ypos + 1, net_id))) {
            return error;
        }
    }

    // Can we go south?
    if (xpos + 1 < PLANE_SIZE) {
        if((error =  _networkinate_item(iplane, xpos + 1, ypos, net_id))) {
            return error;
        }
    }

    // Can we go west?
    if (ypos > 0) {
        if((error = _networkinate_item(iplane, xpos, ypos - 1, net_id))) {
            return error;
        }
    }

    // Return value here is always 0, keeping as int32 in case
    // error handling is required in future.
    return error;
}

int32_t _networkinate_search(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xpos,
    uint32_t ypos,
    uint32_t net_id
) {
    // Get item from iplane at desired position.
    item_t item = iplane[xpos][ypos];

    if(item.type == AIR) {
        return 0;
    }

    return _networkinate_item(iplane, xpos, ypos, net_id);
}

int32_t networkinate_plane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE]
) {
    int32_t error = 0;
    uint32_t net_id = 1;

    // allocate network IDs to items
    for (uint32_t xpos = 0u; xpos < PLANE_SIZE; xpos++) {
        for(uint32_t ypos = 0u; ypos < PLANE_SIZE; ypos++) {
            error = _networkinate_search(
                iplane,
                xpos,
                ypos,
                net_id++
            );

            if(error) {
                return error;
            }
        }
    }
    
    // check for errors
    //TODO move to separate function
    uint32_t current_flattened_net_id = 1;
    for (uint32_t xpos = 0u; xpos < PLANE_SIZE; xpos++) {
        for (uint32_t ypos = 0u; ypos < PLANE_SIZE; ypos++) {
            item_t item = iplane[xpos][ypos];
            if (item.net_id != 0 && item.type != AIR) {
                continue;
            }

            if(item.net_id == 0 && item.type == AIR) {
                continue;
            }

            fprintf(stderr, "Item at %u,%u has no network ID and isn't an Air type\n", xpos, ypos);
            return 1;
        }
    }

    /*
    flatten IDs
    TODO: Move to separate function
    */
    uint32_t flattened_ids_len = PLANE_SIZE_SQR / 2;
    uint32_t flattened_ids[flattened_ids_len];

    // initialize array with zeroes
    for (uint32_t i = 0u; i < flattened_ids_len; i++) {
        flattened_ids[i] = 0;
    }

    // assign flattened IDs for all net_ids
    //TODO move to separate function
    for (uint32_t xpos = 0u; xpos < PLANE_SIZE; xpos++) {
        for (uint32_t ypos = 0u; ypos < PLANE_SIZE; ypos++) {
            item_t item = iplane[xpos][ypos];
            uint32_t net_id = item.net_id;
            if(net_id == 0) {
                continue;
            }
            bool assigned_flattened_id = false;
            for (uint32_t i = 0u; i < flattened_ids_len; i++) {
                uint32_t flattened_id = flattened_ids[i];

                if (flattened_id == net_id) {
                    // net_id already has a flattened variant
                    assigned_flattened_id = true;
                    break;
                }
                
                if(flattened_id == 0) {
                    // add flattened variant
                    flattened_ids[i] = net_id;
                    assigned_flattened_id = true;
                    break;
                }
            }
            
            if(!assigned_flattened_id) {
                fprintf(stderr, "Could not assign flattened ID to net_id %u at item @%u,%u\n", net_id, xpos, ypos);
                return 1;
            }
        }
    }

    // reassign network IDs to large values to prevent conflicts since flattened values start at 1
    //TODO move to separate function
    for (uint32_t xpos = 0u; xpos < PLANE_SIZE; xpos++) {
        for (uint32_t ypos = 0u; ypos < PLANE_SIZE; ypos++) {
            item_t item = iplane[xpos][ypos];
            uint32_t net_id = item.net_id;
            
            if(net_id == 0) {
                continue;
            }

            uint32_t newid = PLANE_SIZE_SQR - (net_id - 1);
            iplane[xpos][ypos].net_id = newid;
        }
    }

    // reassign network IDs to actual flattened values
    //TODO move to separate function
    for (uint32_t xpos = 0u; xpos < PLANE_SIZE; xpos++) {
        for (uint32_t ypos = 0u; ypos < PLANE_SIZE; ypos++) {
            item_t item = iplane[xpos][ypos];

            if(item.net_id == 0) {
                continue;
            }

            for (uint32_t i = 0; i < flattened_ids_len; i++) {
                uint32_t newid = PLANE_SIZE_SQR - (item.net_id - 1);

                if(flattened_ids[i] == newid) {
                    iplane[xpos][ypos].net_id = i + 1;
                    break;
                }
            }
        }
    }

    // TODO move balance report to separate function
    printf("Network Balance Report:\n");
    for (uint32_t net_id = 0u; flattened_ids[net_id] != 0; net_id++) {
        int64_t balance = network_calc_balance(iplane, net_id);
        printf(
            " -> Balance of network #%u is %lld (%s%s%s)\n", 
            net_id, 
            balance, 
            balance >= 0 ? LIGHT_GREEN : LIGHT_RED, 
            balance >= 0 ? "Balanced" : "Unbalanced", 
            LIGHT_WHITE
        );
    }

    return error;
}

void network_color_to_str(
    uint32_t net_id,
    char str[11]
) {
    int32_t color_code = 32 + (net_id % 6);
    sprintf(str, "\033[1;%dm", color_code);
}

int64_t network_calc_balance(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t net_id
) {
    // count sources and sinks in the network of net_id
    uint32_t sources = 0;
    uint32_t sinks = 0;

    for (uint32_t xpos = 0; xpos < PLANE_SIZE; xpos++) {
        for (uint32_t ypos = 0; ypos < PLANE_SIZE; ypos++) {
            item_t item = iplane[xpos][ypos];
            if(item.net_id != net_id) {
                continue;
            }
            switch(item.type) {
                case SOURCE:
                    sources++;
                    break;
                case SINK:
                    sinks++;
                    break;
                default:
                    break;
            }
        }
    }

    return ((int64_t) sources * UNITS_PER_SOURCE) - (int64_t) sinks;
}
