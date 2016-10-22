#include "include/player.h"
#include <cstring>

player::player(int x, int y):
    coord(x, y) {
}

size_t player::write_bytes(char* buffer) const {
    memcpy(buffer, &coord, sizeof(point));
    return sizeof(point);
}

