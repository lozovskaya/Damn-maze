#include "include/player.h"
#include <cstring>

player::player(int x, int y):
    coord(x, y) {
}

size_t player::write_bytes(char* buffer) const {
    memcpy(buffer, &coord, sizeof(point));
    return sizeof(point);
}

void player::move(const std::vector<int> &buttons) {
    for (int c : buttons) {
        switch (c) {
        case 'w':
            coord.y -= 1; // Here will be change speed
            break;
        case 's':
            coord.y += 1; //
            break;
        case 'a':
            coord.x -= 1; //
            break;
        case 'd':
            coord.x += 1; //
            break;
        }
    }
}
