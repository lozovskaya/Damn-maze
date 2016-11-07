#include "include/field.h"
#include "include/rand.h"
#include <cstring>
#include <iostream>
#include <vector>

void field::room_walls(int x1, int y1, int x2, int y2) {
    int entire_pos_x, entire_pos_y, entire_type;
    if (x1 > x2) {
        std::swap(x1, x2);
    }
    if (y1 > y2) {
        std::swap(y1, y2);
    }
    for (int i = x1; i <= x2; i++) {
        data[i][y1] = cell(cell_type::wall);
        data[i][y2] = cell(cell_type::wall);
    }
    for (int i = y1; i <= y2; i++) {
        data[x1][i] = cell(cell_type::wall);
        data[x2][i] = cell(cell_type::wall);
    }
    entire_type = get_rand(0, 1);
    if (entire_type) {
        entire_pos_x = get_rand(0, 1) ? x1 : x2;
        entire_pos_y = get_rand(y1 + 1, y2 - 1);
    } else {
        entire_pos_x = get_rand(x1 + 1, x2 - 1);
        entire_pos_y = get_rand(0, 1) ? y1 : y2;
    }
    data[entire_pos_x][entire_pos_y] = cell(cell_type::ground);
}

void field::make_rooms(std::set<std::pair<int, int> > & corners) {
    for (auto it = corners.begin(); it != corners.end(); ++(++it)) {
        room_walls(it->first, it->second, std::next(it)->first, std::next(it)->second);
    }
}

void field::generate_roomfilled_field() {
    int hole_x, hole_y;
    int num_of_rooms = height * width / 2500;
    int num_of_holes = height * width / 500;
    std::set<std::pair<int, int> > room_corners;
    for (int i = 0; i < num_of_rooms; i++) {
        room_corners.insert(std::make_pair(get_rand(0, height - 1), get_rand(0, width - 1)));
        room_corners.insert(std::make_pair(get_rand(0, height - 1), get_rand(0, width - 1)));
    }
    for (int i = 0; i < num_of_holes; i++) {
        hole_x = get_rand(0, height - 1);
        hole_y = get_rand(0, width - 1);
        data[hole_x][hole_y] = cell(cell_type::hole);
    }
    make_rooms(room_corners);
}

void field::generate_random_field() {
    int rand_cell_type;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rand_cell_type = get_rand(1, 10);
            switch (rand_cell_type)
            {
            case 1:
            case 2:
            case 3:
                data[i][j] = cell(cell_type::wall);
                break;

            case 4:
                data[i][j] = cell(cell_type::hole);
                break;

            default:
                data[i][j] = cell(cell_type::ground);
                break;
            }
        }
    }
}

void field::generate_blank_field() {
    int hole_x, hole_y;
    for (int i = 0; i < width; i++) {
        data[0][i] = data.back()[i] = cell(cell_type::wall);
    }
    hole_x = get_rand(1, height - 2);
    hole_y = get_rand(1, width - 2);
    data[hole_x][hole_y] = cell(cell_type::hole);
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

