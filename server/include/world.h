#ifndef WORLD_H
#define WORLD_H

#include "field.h"
#include "player.h"
#include "point.h"
#include <map>
#include <memory>
#include <vector>


class World {
    int max_player_id;
    std::map<int, std::shared_ptr<player> > players;
    field F;

  public:
    World();
    void write_field() const;
    void update_player(int player_id, const std::vector<int> &buttons);
    int add_player();
    size_t write_bytes(char* buffer) const;
};

#endif // WORLD_H
