#include <iostream>
#include <fstream>
#include <vector>
#include "include/field.h"
#include "include/point.h"
#include "include/net.h"
#include "include/world.h"

using namespace std;


int main() {
    World world;
    if (init_net()) {
        printf("failed in init_net\n");
        return 0;
    }
    SOCKET client_socket;
    if (connect_with_client(client_socket)) {
        printf("can't connect\n");
        return 0;
    }
    world.write_field();
    update_net(client_socket, world);
}
