#include <stdlib.h>
#include "items.h"

char* item_type_to_str(item_type_t item_type) {
    switch(item_type) {
        case AIR:
            return "⬛️"; // visually different enough to the rest of the chars
        case PIPE:
            return "🧊"; // it looks like a pipe, no?
        case SOURCE:
            return "🌊"; // as in 'out'...
        case SINK:
            return "💧"; // as in 'in'...
        default:
            return "";
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
        default:
            return "?";
    }
}
