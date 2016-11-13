#ifndef FIELD_H
#define FIELD_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

const static int WORLD_FIELD_WIDTH = 50;
const static int WORLD_FIELD_HEIGHT = 50;
const static int CELL_WIDTH = 10;
const static int CELL_HEIGHT = 10;

enum class field_type {
    blank = 1,
    random = 2,
    roomfilled = 3,
    dfs_ed = 4
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
    std::pair<int, int> get_pair() const {
        return std::make_pair(x, y);
    }
    bool operator != (const cell &other) const {
        return x != other.x || y != other.y;
    }
};

class field {
    int height, width;
    std::vector<std::vector<cell> > data;

    void generate_blank_field();
    void fill_with(cell_type fill);

    void generate_random_field();

    void generate_roomfilled_field();
    void make_rooms(std::set<std::pair<int, int> > & corners);
    void room_walls(int x1, int y1, int x2, int y2);

    void generate_dfs_field();
    void dfs_field(int x, int y, std::set<std::pair<int, int> > &room_centers);
    cell generate_room(cell pos, int size);
    bool is_free(cell pos, cell prev) const;

    bool is_valid(int x, int y) const;
    std::vector<cell> get_neighbours(cell pos) const;
    std::vector<cell> get_neighbours_wide(cell pos) const;
    template <typename T>
    std::vector<cell> get_neighbours_if(cell pos, const T& condition) const;
    template <typename T>
    std::vector<cell> get_neighbours_wide_if(cell pos, const T& condition) const;


  public:
    field() : height(0), width(0){
    }
    field(int h, int w, field_type type=field_type::blank);
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



template <typename T>
std::vector<cell> field::get_neighbours_if(cell pos, const T& condition) const {
    std::vector<cell> good_neighbours, all_neighbours = get_neighbours(pos);
    good_neighbours.resize(all_neighbours.size());
    auto last = std::copy_if(all_neighbours.begin(), all_neighbours.end(), good_neighbours.begin(), condition);
    good_neighbours.resize(distance(good_neighbours.begin(), last));
    return good_neighbours;
}
template <typename T>
std::vector<cell> field::get_neighbours_wide_if(cell pos, const T& condition) const {
    std::vector<cell> good_neighbours, all_neighbours = get_neighbours_wide(pos);
    good_neighbours.resize(all_neighbours.size());
    auto last = std::copy_if(all_neighbours.begin(), all_neighbours.end(), good_neighbours.begin(), condition);
    good_neighbours.resize(distance(good_neighbours.begin(), last));
    return good_neighbours;

}
#endif // FIELD_H
