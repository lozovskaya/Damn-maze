#include "include/field.h"
#include "include/net.h"
#include "include/point.h"
#include "include/world.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


int main() {
    srand(time(0));
    World world;
    Net net;
    world.write_field();
    while (true)
    {
        net.update(world);
        world.update();
    }
}
