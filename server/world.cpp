#include "include/world.h"
#include <fstream>
#include <memory>
#include "include/rand.h"

const static int WORLD_FIELD_WIDTH = 20, WORLD_FIELD_HEIGHT = 10;

World::World():
    max_player_id(0),
    F(WORLD_FIELD_HEIGHT, WORLD_FIELD_WIDTH)
    {}

void World::write_field() const {
    std::ofstream output;
    output.open("field");
    F.write_out(output);
    output.close();
};

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

int World::add_player() {
   int player_id = max_player_id++;
   int x = get_rand(0, F.height), y = get_rand(0, F.width);
   while (F[x][y].type != cell_type::ground) {
        x = get_rand(0, F.height), y = get_rand(0, F.width);
   }
   players[player_id] = std::shared_ptr<player>(new player(x, y));
   return player_id;
}
