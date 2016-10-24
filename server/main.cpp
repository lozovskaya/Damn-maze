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
    Net net;
    SOCKET client_socket;
    if (net.connect_with_client(client_socket)) {
        printf("can't connect\n");
        return 0;
    }
    world.write_field();
	while (true)
	{
		net.update(client_socket, world);
	}
}
