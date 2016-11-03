#ifndef FIELD_H
#define FIELD_H

#include <cstring>
#include <iostream>
#include <vector>

#define FIELD_X 10
#define FIELD_Y 10

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
    field(int h, int w);    
    void write_out(std::ostream& out) const;
    int write_bytes(char* buff) const;
    std::vector<cell> &operator[](int i) {
        return data[i];
    }
};

#endif // FIELD_H
