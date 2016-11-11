#include "../include/field.h"
#include "../include/rand.h"
#include <vector>
#include <utility>
#include <map>
#include <iostream>

bool field::is_free(cell pos, cell prev) const {
    if (data[pos.x][pos.y].type == cell_type::ground or 
        data[pos.x][pos.y].type == cell_type::will_be_ground) {
        return false;
    }
    std::vector<cell> neighbours = get_neighbours(pos);
    for (auto c : neighbours) {
        if (c != prev && (c.type == cell_type::ground or c.type == cell_type::will_be_ground)) {
            return false;
        }
    }
    return true;
}

cell field::generate_room(cell pos, int size) {
    int x_coef = get_rand(5, 9), y_coef = get_rand(5, 9);
    std::vector<cell> queue;
    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            if (!is_valid(pos.x + i, pos.y + j)) {
                continue;
            }
            int dist = i * i * x_coef + j * j * y_coef;
            if (dist < size * 2) {
                data[pos.x + i][pos.y + j].type = cell_type::ground;
            } else if (dist < size * 3) {
                queue.push_back(data[pos.x + i][pos.y + j]);
            }
        }
    }
    int idx = get_rand(0, queue.size());
    return queue[idx];
}

void field::dfs_field(int x, int y) {
    data[x][y].type = cell_type::will_be_ground;
    cell u = data[x][y];

    if (get_rand(0, 100) < 1) {
        cell v = generate_room(data[x][y], 25);
        dfs_field(v.x, v.y);
    }
    if (get_rand(0, 30) == 0) {
        data[x][y].type = cell_type::ground;
        return;
    }
    int amount_of_free = 0;
    std::vector<cell> neighbours = get_neighbours(u);
    for (auto c : neighbours) {
        if (is_free(c, u)) {
            amount_of_free++;
        }
    }
    int go = get_rand(0, amount_of_free);
    for (auto c : neighbours) {
        if (is_free(c, u) && go == 0) {
            dfs_field(c.x, c.y);
        }
        if (is_free(c, u)) {
            go--;
        }
    }
    data[x][y].type = cell_type::ground;
}

void field::generate_dfs_field() {
    fill_with(cell_type::wall);
    dfs_field(get_rand(height / 3, 2 * height / 3), get_rand(width / 3, 2 * width / 3));
    height *= 2;
    width *= 2;
    std::vector<std::vector<cell> > new_data(height, std::vector<cell>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new_data[i][j] = cell(i, j, data[i / 2][j / 2].type);
        }
    }
    data = new_data;
    std::vector<cell> will_be_wall;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int wall_cnt = 0;
            std::vector<cell> current_neighbours = get_neighbours(data[i][j]);
            for (auto neighbour : current_neighbours) {
                if (neighbour.type == cell_type::wall) {
                    wall_cnt++;
                }
            }
            if (wall_cnt >= 2) {
                will_be_wall.push_back(data[i][j]);
            }
        }
    }
    for (auto wall : will_be_wall) {
        data[wall.x][wall.y].type = cell_type::wall;
    }
}
