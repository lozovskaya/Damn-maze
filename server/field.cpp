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
    for (std::set<std::pair<int, int> >::iterator it = corners.begin(); it != corners.end(); it++) {
        std::set<std::pair<int, int> >::iterator it2 = it;
        it++;
        room_walls(it2->first, it2->second, it->first, it->second);
    }
}

field::field(int h, int w, field_type type) {
    int num_of_rooms, num_of_holes;
    std::set<std::pair<int, int> > room_corners;
    int hole_x, hole_y, rand_cell_type;
    switch (type) {
    case field_type::blank:
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < w; i++) {
            data[0][i] = data.back()[i] = cell(cell_type::wall);
        }
        hole_x = get_rand(1, h - 2);
        hole_y = get_rand(1, w - 2);
        data[hole_x][hole_y] = cell(cell_type::hole);
        break;

    case field_type::random:
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
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
        break;

    case field_type::roommed:
        num_of_rooms = h * w / 2500;
        num_of_holes = h * w / 500;
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < num_of_rooms; i++) {
            room_corners.insert(std::make_pair(get_rand(0, h - 1), get_rand(0, w - 1)));
            room_corners.insert(std::make_pair(get_rand(0, h - 1), get_rand(0, w - 1)));
        }
        for (int i = 0; i < num_of_holes; i++) {
            hole_x = get_rand(0, h - 1);
            hole_y = get_rand(0, w - 1);
            data[hole_x][hole_y] = cell(cell_type::hole);
        }
        make_rooms(room_corners);
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

