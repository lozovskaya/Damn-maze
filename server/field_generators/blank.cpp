#include "../include/field.h"
#include "../include/rand.h"
#include <cstring>
#include <iostream>


void field::generate_blank_field() {
    fill_with(cell_type::ground);
/*  hole_x = get_rand(1, height - 2);
    hole_y = get_rand(1, width - 2);
    data[hole_x][hole_y] = cell(hole_x, hole_y, cell_type::hole);*/
}
