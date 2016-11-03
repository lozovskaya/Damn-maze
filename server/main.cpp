#include "include/field.h"
#include "include/net.h"
#include "include/point.h"
#include "include/world.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


int main() {
    World world;
    Net net;
    world.write_field();
    while (true)
    {
        net.update(world);
        world.update();
    }
}
