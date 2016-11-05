#include "include/rand.h"
#include "include/world.h"
#include <fstream>
#include <memory>

const static int WORLD_FIELD_WIDTH = 20, WORLD_FIELD_HEIGHT = 10;

World::World():
    max_player_id(0), 
    time(0), 
    F(WORLD_FIELD_HEIGHT, WORLD_FIELD_WIDTH) 
    {}

void World::update() {
    for (auto player : players) {
        move_player(player.second);
    }
    time = ((double) clock()) / CLOCKS_PER_SEC; 
}

bool collision(point s1, point f1, point s2, point f2) { 
    return true;
}

bool square_intersect(point coord, point fin, int i, int j) {
    bool intersect = false;
    point start = point(i * FIELD_X, j * FIELD_Y); 
    point end = point((i + 1) * FIELD_X, j * FIELD_Y); 
    intersect |= collision(coord, fin, start, end); 
    end = point(i * FIELD_X, (j + 1) * FIELD_Y); 
    intersect |= collision(coord, fin, start, end); 
    start  = point((i + 1) * FIELD_X, (j + 1) * FIELD_Y); 
    intersect |= collision(coord, fin, start, end); 
    end = point((i + 1) * FIELD_X, j * FIELD_Y); 
    intersect |= collision(coord, fin, start, end); 
    return intersect;
}



double World::bin_by_time(point coord, point speed, double min_time, double max_time) { 
    while ((max_time + min_time) / 2 > 0.01)
    {
        bool flag = false;
        point fin = coord + speed * (max_time + min_time) / 2;
        for (int i = 0; i < F.height; i++) { 
            for (int j = 0; j < F.width; j++) { 
                if (F.data[i][j].type == cell_type::wall) { //Just when it is wall FIXME
                    flag = square_intersect(coord, fin, i, j);
                    }
                if (flag) break;
            }
            if(flag) break;
        }
        if (flag) {
            max_time = (max_time + min_time) / 2;
        }
        else {
            min_time = (max_time + min_time) / 2;
        }
    }
    return (max_time + min_time) / 2;
}

double World::time_of_movement(point coord, point speed) {
    return bin_by_time(coord, speed, 0, ((double) clock()) / CLOCKS_PER_SEC - time);
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
   int x = get_rand(0, F.height), y = get_rand(0, F.width);
   while (F[x][y].type != cell_type::ground) {
        x = get_rand(0, F.height), y = get_rand(0, F.width);
   }
   players[player_id] = std::shared_ptr<player>(new player(x, y));
   return player_id;
}
