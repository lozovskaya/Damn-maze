#ifndef PLAYER_H
#define PLAYER_H

#include "point.h"
#include <cstddef>
#include <vector>

class player {
    point coord;
  public:
    player();
    player(int x, int y);
    size_t write_bytes(char* buffer) const;
    void move(const std::vector<int> &buffer);
};

#endif // PLAYER_H
