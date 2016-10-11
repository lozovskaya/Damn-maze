#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <cstring>
#include <vector>

enum class cell_type {
    ground = 0,
    wall = 1,
    hole = 2,
};

struct cell {
    cell_type type;
    cell(cell_type t = cell_type::ground) : type(t) {
    }
};

struct field {
    int height, width;
    std::vector<std::vector<cell> > data;


    field() : height(0), width(0){
    }
    field(int h, int w) {
        height = h;
        width = w;
        data.resize(h, std::vector<cell>(w));
        for (int i = 0; i < h; i++) {
            data[0][i] = data.back()[i] = cell(cell_type::wall);
        }
    }
    
    void write_out(std::ostream& out) const {
        out << height << ' ' << width << '\n';
        for (const auto & raw : data) {
            for (const auto & cell : raw) {
                out << int(cell.type) << ' ';
            }
            out << '\n';
        }
    }

    int write_bytes(char* buff) const {
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
};

#endif // FIELD_H
