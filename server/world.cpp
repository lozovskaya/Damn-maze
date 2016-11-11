#include "include/rand.h"
#include "include/world.h"
#include <fstream>
#include <memory>


World::World():
    max_player_id(0), 
    time(0)
    {
    F = field(WORLD_FIELD_HEIGHT, WORLD_FIELD_WIDTH, field_type::dfs_ed);
    }

void World::update() {
    for (auto player : players) {
        move_player(player.second);
    }
    time = ((double) clock()) / CLOCKS_PER_SEC; 
}

bool polygon_intersect_segment(segment segm, const std::vector <point> & polygon) {
    for (size_t i = 0; i < polygon.size(); i++) {
        if (segm & segment(polygon[i], polygon[(i + 1) % polygon.size()])) 
            return true;
    }
    return false;
}

std::vector <point> make_square(int i, int j) {
    std::vector <point> square;
    square.push_back(point(i * CELL_WIDTH, j * CELL_HEIGHT));
    square.push_back(point(i * CELL_WIDTH, (j + 1) * CELL_HEIGHT));
    square.push_back(point((i + 1) * CELL_WIDTH, (j + 1) * CELL_HEIGHT));
    square.push_back(point((i + 1) * CELL_WIDTH, j * CELL_HEIGHT));
    return square;
}

double World::search_by_time(point coord, point speed, double max_time) {
    double check_time, min_time = 0;
    for (int k = 0; k < 20; k++) {
        check_time = (max_time + min_time) / 2;
        bool obstructed = false;
        point begin = coord, end = coord + speed * check_time; 
        for (int i = 0; i < F.get_height() && !obstructed; i++) { 
            for (int j = 0; j < F.get_width() && !obstructed; j++) { 
                if (F[i][j].type == cell_type::wall) { //Just when it is wall FIXME
                    obstructed = polygon_intersect_segment(segment(begin, end), make_square(i, j));
                } 
            }
        }
        if (obstructed) {
            max_time = check_time;
        }
        else {
            min_time = check_time;
        }
    }
    return check_time;
}

double World::time_of_movement(point coord, point speed) {
    return search_by_time(coord, speed, ((double) clock()) / CLOCKS_PER_SEC - time);
}

void World::move_player(std::shared_ptr <player> player) {
    point coord = player->get_coord();
    point speed = player->get_speed();
    player->move(time_of_movement(coord, speed));
}

void World::write_field() const {
    std::ofstream output;
    output.open("field");
    F.write_out(output);
    output.close();
}

size_t World::write_bytes(char* buffer) const {
    size_t result = F.write_bytes(buffer);
    int amount_of_players = players.size();
    memcpy(buffer + result, &amount_of_players, sizeof(int));
    result += sizeof(int);
    for (auto player_ptr : players) {
        result += player_ptr.second->write_bytes(result + buffer);
    }
    return result;
}

void World::change_player_state(int player_id, const std::vector<int> & buttons) {
    players[player_id]->change_state(buttons);
}

int World::add_player() {
   int player_id = max_player_id++;
   int x = get_rand(0, F.get_height()), y = get_rand(0, F.get_width());
   while (F[x][y].type != cell_type::ground) {
        x = get_rand(0, F.get_height()), y = get_rand(0, F.get_width());
   }
   players[player_id] = std::shared_ptr<player>(new player(x, y));
   return player_id;
}
