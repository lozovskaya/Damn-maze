#ifndef WORLD_H
#define WORLD_H

#include "point.h"
#include "field.h"
#include "player.h"
#include <memory>
#include <map>


class World {
    int max_player_id;
    std::map<int, std::shared_ptr<player> > players;
    field F;
  public:
    World();
    void write_field() const;
    size_t write_bytes(char* buffer) const;
    int add_player();
};

#endif // WORLD_H
