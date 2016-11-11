#include "../include/field.h"
#include "../include/rand.h"
#include <cstring>
#include <iostream>


void field::generate_blank_field() {
    int hole_x, hole_y;
    for (int i = 0; i < width; i++) {
        data[0][i] = cell(0, i, cell_type::wall);
        data[height - 1][i] = cell(height - 1, i, cell_type::wall);
    }
    hole_x = get_rand(1, height - 2);
    hole_y = get_rand(1, width - 2);
    data[hole_x][hole_y] = cell(hole_x, hole_y, cell_type::hole);
}
