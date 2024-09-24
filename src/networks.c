#include "networks.h"

int32_t _networkinate_item(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xpos,
    uint32_t ypos,
    uint32_t xlen,
    uint32_t ylen,
    uint32_t net_id
) {
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
        _networkinate_item(iplane, xpos - 1, ypos, xlen, ylen, net_id);
    }

    // Can we go east?
    if (ypos < ylen - 1) {
        _networkinate_item(iplane, xpos, ypos + 1, xlen, ylen, net_id);
    }

    // Can we go south?
    if (xpos < xlen - 1) {
        _networkinate_item(iplane, xpos + 1, ypos, xlen, ylen, net_id);
    }

    // Can we go west?
    if (ypos > 0) {
        _networkinate_item(iplane, xpos, ypos - 1, xlen, ylen, net_id);
    }

    // Return value here is always 0, keeping as int32 in case
    // error handling is required in future.
    return 0;
}

int32_t _networkinate_search(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xpos,
    uint32_t ypos,
    uint32_t xlen,
    uint32_t ylen,
    uint32_t *net_id
) {
    // Get item from iplane at desired position.
    item_t item = iplane[xpos][ypos];
    
    // we are processing a new network so let's increment
    // the current network ID
    if (item.type != AIR && item.net_id == 0) {
        (*net_id)++;
    }

    return _networkinate_item(iplane, xpos, ypos, xlen, ylen, *net_id);
}

int32_t networkinate_plane(
    item_t iplane[PLANE_SIZE][PLANE_SIZE],
    uint32_t xlen,
    uint32_t ylen,
    uint32_t *net_id
) {
    int32_t error = 0;

    for (uint32_t xpos = 0u; xpos < xlen; xpos++) {
        for(uint32_t ypos = 0u; ypos < ylen; ypos++) {
            error = _networkinate_search(
                iplane,
                xpos,
                ypos,
                xlen,
                ylen,
                net_id
            );

            if(error) {
                return error;
            }
        }
    }
    
    return error;
}
