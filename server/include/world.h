#ifndef WORLD_H
#define WORLD_H

#include "field.h"
#include "player.h"
#include "point.h"
#include <map>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>


class World {
    int max_player_id;
    int time = 0; //<-
    std::map<int, std::shared_ptr<player> > players;
    field F;

  public:
    World();
    void update();
    void write_field() const;
    void change_player_state(int player_id, const std::vector<int> &buttons);
    void move_player(std::shared_ptr <player> player);
    int check_move(point coord, point speed); //<-
    int add_player();
    size_t write_bytes(char* buffer) const;
};

#endif // WORLD_H
