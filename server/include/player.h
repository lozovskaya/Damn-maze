#ifndef PLAYER_H
#define PLAYER_H

#include "point.h"
#include <cstddef>
#include <vector>

class player {
    point coord;
    point speed;
  public:
    player();
    player(int x, int y);
    size_t write_bytes(char* buffer) const;
    void change_state(const std::vector<int> &buffer);
    point get_coord() const;
    point get_speed() const;
    void move(int t);
};

#endif // PLAYER_H
