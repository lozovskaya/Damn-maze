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
#include <ctime>


class World {
    int max_player_id;
    double time;
    std::map<int, std::shared_ptr<player> > players;
    field F;

    
    double time_of_movement(point coord, point speed);
    void move_player(std::shared_ptr <player> player);
    double bin_by_time(point coord, point speed, double min_time, double max_time); 

  public:
    World();
    void update();
    void change_player_state(int player_id, const std::vector<int> &buttons);
    void write_field() const;
    int add_player();
    size_t write_bytes(char* buffer) const;
};

#endif // WORLD_H
