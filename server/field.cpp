#include "include/field.h"
#include "include/rand.h"
#include <cstring>
#include <iostream>
#include <vector>


bool field::is_valid(int x, int y) const {
    return (0 <= x && x < height) && (0 <= y && y < width);
}

field::field(int h, int w, field_type type) {
    height = h;
    width = w;
    data.resize(height, std::vector<cell>(width));
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

    case field_type::dfs_ed:
        generate_dfs_field();
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
            memcpy(buff, &elem.type, sizeof(elem.type));
            buff += sizeof(elem.type);
        }
    }
    return buff - last;
}

void field::fill_with(cell_type fill) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            data[i][j] = cell(i, j, fill);
        }
    }
}

std::vector<cell> field::get_neighbours(cell pos) const {
    int x = pos.x, y = pos.y;
    std::vector<cell> neighbours;
    if (is_valid(x, y - 1)) {
        neighbours.push_back(data[x][y - 1]);
    }
    if (is_valid(x, y + 1)) {
        neighbours.push_back(data[x][y + 1]);
    }
    if (is_valid(x - 1, y)) {
        neighbours.push_back(data[x - 1][y]);
    }
    if (is_valid(x + 1, y)) {
        neighbours.push_back(data[x + 1][y]);
    }
    return neighbours;
}

std::vector<cell> field::get_neighbours_wide(cell pos) const {
    int x = pos.x, y = pos.y;
    std::vector<cell> neighbours;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (is_valid(x + i, y + j)) {
                neighbours.push_back(data[x + i][y + j]);
            }
        }
    }
    return neighbours;
}
