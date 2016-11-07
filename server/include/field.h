#ifndef FIELD_H
#define FIELD_H

#include <cstring>
#include <iostream>
#include <vector>
#include <set>

const static int WORLD_FIELD_WIDTH = 50;
const static int WORLD_FIELD_HEIGHT = 50;
const static int CELL_X = 10;
const static int CELL_Y = 10;
const static int USED_FIELD_TYPE = 3; //will be used now
const static int FIELD_TYPE_1 = 1; //BLANCK
const static int FIELD_TYPE_2 = 2; //RANDOM
const static int FIELD_TYPE_3 = 3; //
const static int num_of_rooms = 5;
const static int num_of_holes = 20;

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
    field(int h, int w, int type);    
    void write_out(std::ostream& out) const;
    int write_bytes(char* buff) const;
    std::vector<cell> &operator[](int i) {
        return data[i];
    }
};

#endif // FIELD_H
