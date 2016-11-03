#include "include/field.h"
#include "include/rand.h"
#include <cstring>
#include <iostream>
#include <vector>

field::field(int h, int w) {
    height = h;
    width = w;
    data.resize(h, std::vector<cell>(w));
    for (int i = 0; i < w; i++) {
        data[0][i] = data.back()[i] = cell(cell_type::wall);
    }
    int hole_x = get_rand(1, h - 2);
    int hole_y = get_rand(1, w - 2);
    data[hole_x][hole_y] = cell(cell_type::hole);
}

void field::write_out(std::ostream& out) const {
    out << height << ' ' << width << '\n';
    for (const auto & raw : data) {
        for (const auto & cell : raw) {
            out << int(cell.type) << ' ';
        }
        out << '\n';
    }
}

int field::write_bytes(char* buff) const {
    char* last = buff;
    memcpy(buff, &height, 2 * sizeof(int));
    buff += 2 * sizeof(int);
    for (const auto &v : data) {
        for (const auto &elem : v) {
            memcpy(buff, &elem, sizeof(elem));
            buff += sizeof(elem);
        }
    }
    
    return buff - last;
}

