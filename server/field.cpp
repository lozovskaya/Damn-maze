#include "include/field.h"
#include <cstring>
#include <iostream>
#include <vector>



field::field(int h, int w, field_type type) {
    height = h;
    width = w;
    data.resize(height, std::vector<cell>(width));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            data[i][j] = cell(i, j);
        }
    }
    switch (type) {
    case field_type::blank:
        generate_blank_field();
        break;

    case field_type::random:
        generate_random_field();
        break;

    case field_type::roomfilled:
        generate_roomfilled_field();
        break;

    default:
        throw std::runtime_error("No exist field type, field init error");
        break;
    }
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

