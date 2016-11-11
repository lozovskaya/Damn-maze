#include "../include/field.h"
#include "../include/rand.h"
#include <cstring>
#include <iostream>


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
