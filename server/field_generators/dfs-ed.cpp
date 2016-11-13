#include "../include/field.h"
#include "../include/rand.h"
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <iostream>

bool field::is_free(cell pos, cell prev) const {
    if (data[pos.x][pos.y].type == cell_type::ground) {
        return false;
    }
    std::vector<cell> bad_neighbours = get_neighbours_if(pos, [prev](const cell &c) {
                                        return c != prev && (c.type == cell_type::ground);
                                        });
    return (bad_neighbours.empty());
}

cell field::generate_room(cell pos, int square) {
    int x_coef = get_rand(5, 9), y_coef = get_rand(5, 9);
    std::vector<cell> queue;
    for (int i = -square; i <= square; i++) {
        for (int j = -square; j <= square; j++) {
            if (!is_valid(pos.x + i, pos.y + j)) {
                continue;
            }
            int dist = i * i * x_coef + j * j * y_coef;
            cell &current = data[pos.x + i][pos.y + j];
            if (dist < square) {
                current.type = cell_type::ground;
            } else if (square < dist && !is_free(current, pos)) {
                queue.push_back(current);
            }
        }
    }
    int idx = get_rand(0, queue.size());
    return queue[idx];
}

void field::dfs_field(int x, int y, std::set<std::pair<int, int> > &room_centers) {
    data[x][y].type = cell_type::ground;
    cell u = data[x][y];

    bool can_create_room = true;
    for (auto center : room_centers) {
        if (hypot(x - center.first, y - center.second) < 30) {
            can_create_room = false;
        }
    }


    if (get_rand(0, 100) < 10 && can_create_room) {
        std::cout << "room" << '\n';
        cell v = generate_room(data[x][y], 50);
        room_centers.insert(std::make_pair(v.x, v.y));
        dfs_field(v.x, v.y, room_centers);
    }


    int roads = 1;
    if (get_rand(0, 50) < 8) {
        roads++;
    }
    for (int i = 0; i < roads; i++) {
        std::vector<cell> neighbours = get_neighbours_if(u, 
                [&](const cell &c) {
                    return this->is_free(c, u);
                });
        int amount_of_free = neighbours.size();
        std::cout << u.x << ' ' << u.y << ' ' << amount_of_free << '\n';
        if (amount_of_free == 0) {
            return;
        }
        int go = get_rand(0, amount_of_free);
        dfs_field(neighbours[go].x, neighbours[go].y, room_centers);
    }
    return;
}

void field::generate_dfs_field() {
    fill_with(cell_type::wall);
    std::set<std::pair<int, int> > room_centers;
    dfs_field(get_rand(height / 3, 2 * height / 3), get_rand(width / 3, 2 * width / 3), room_centers);
    height = height * 2 + 2;
    width = width * 2 + 2;
    std::vector<std::vector<cell> > new_data(height, std::vector<cell>(width));
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            new_data[i][j] = cell(i, j, data[(i - 1) / 2][(j - 1) / 2].type);
        }
    }
    for (int j = 0; j < width; j++) {
        new_data[0][j] = cell(0, j, cell_type::wall);
        new_data.back()[j] = cell(height - 1, j, cell_type::wall);
    }
    for (int i = 0; i < height; i++) {
        new_data[i][0] = cell(i, 0, cell_type::wall);
        new_data[i].back() = cell(i, width - 1, cell_type::wall);
    }
    data = new_data;
    std::vector<cell> will_be_wall;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::vector<cell> current_neighbours = get_neighbours_if(data[i][j], [](const cell &c) {
                        return c.type == cell_type::wall;
                    });
            if (current_neighbours.size() >= 2) {
                will_be_wall.push_back(data[i][j]);
            }
        }
    }
    for (auto wall : will_be_wall) {
        data[wall.x][wall.y].type = cell_type::wall;
    }
}
