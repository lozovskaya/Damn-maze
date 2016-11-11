#ifndef FIELD_H
#define FIELD_H

#include <cstring>
#include <iostream>
#include <vector>
#include <set>

const static int WORLD_FIELD_WIDTH = 50;
const static int WORLD_FIELD_HEIGHT = 50;
const static int CELL_WIDTH = 10;
const static int CELL_HEIGHT = 10;

enum class field_type {
    blank = 1,
    random = 2,
    roomfilled = 3,
};

enum class cell_type {
    ground = 0,
    wall = 1,
    hole = 2,
};

struct cell {
    int x, y;
    cell_type type;
    cell(int _x=0, int _y=0, cell_type t=cell_type::ground) : x(_x), y(_y), type(t) {
    }
};

class field {
    void generate_blank_field();
    void generate_random_field();
    void generate_roomfilled_field();
    void make_rooms(std::set<std::pair<int, int> > & corners);
    void room_walls(int x1, int y1, int x2, int y2);
    int height, width;
    std::vector<std::vector<cell> > data;

  public:
    field() : height(0), width(0){
    }
    field(int h, int w, field_type type=field_type::roomfilled);
    void write_out(std::ostream& out) const;
    int write_bytes(char* buff) const;

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }
    std::vector<cell> &operator[](int i) {
        return data[i];
    }
};

#endif // FIELD_H
