#include "include/field.h"
#include "include/rand.h"
#include <cstring>
#include <iostream>
#include <vector>

void room_walls(std::vector<std::vector<cell> > & data, int x1, int y1, int x2, int y2) {
    if (x1 > x2) {
        std::swap(x1, x2);
    }if (y1 > y2) {
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
    if (get_rand(0, 1)) {
        data[get_rand(0, 1) ? x1 : x2][get_rand(y1  + 1, y2 - 1)] = cell(cell_type::ground);
    }
    else {
        data[get_rand(x1 + 1, x2 - 1)][get_rand(0, 1) ? y1 : y2] = cell(cell_type::ground);
    }
}

void make_rooms(std::vector<std::vector<cell> > & data, std::set<std::pair<int, int> > & corners) {
    for (std::set<std::pair<int, int> >::iterator it = corners.begin(); it != corners.end(); it++) {
        std::set<std::pair<int, int> >::iterator it2 = it;
        it++;
        room_walls(data, it2->first, it2->second, it->first, it->second);
    }
}

field::field(int h, int w, int type) {
    std::set<std::pair<int, int> > room_corners;
    switch (type) {
    case FIELD_TYPE_1:
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < w; i++) {
            data[0][i] = data.back()[i] = cell(cell_type::wall);
        }
        data[get_rand(1, h - 2)][get_rand(1, w - 2)] = cell(cell_type::hole);
        break;

    case FIELD_TYPE_2:
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                switch (get_rand(1, 10))
                {
                case 1:
                    data[i][j] = cell(cell_type::wall);
                    break;

                case 2:
                    data[i][j] = cell(cell_type::wall);
                    break;

                case 3:
                    data[i][j] = cell(cell_type::wall);
                    break;

                case 4:
                    data[i][j] = cell(cell_type::hole);
                    break;

                default:
                    break;
                }
            }
        }
        break;

    case FIELD_TYPE_3:
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < num_of_rooms; i++) {
            room_corners.insert(std::make_pair(get_rand(0, h - 1), get_rand(0, w - 1)));
            room_corners.insert(std::make_pair(get_rand(0, h - 1), get_rand(0, w - 1)));
        }
        for (int i = 0; i < num_of_holes; i++) {
            data[get_rand(0, h - 1)][get_rand(0, w - 1)] = cell(cell_type::hole);
        }
        make_rooms(data, room_corners);
        break;

    default:
        throw std::runtime_error("No exist field type");
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

