#ifndef NET_H
#define NET_H

#include "net_includes.h"
#include "world.h"

class Net {
    SOCKET my_socket;
    char buffer[BUFF_SIZE];
    int get_data_timeout(SOCKET client_socket, char* buff, size_t len, int sec = 0, int usec = 10000);
    int process_keys_update(World &world);
  public:
    Net();
    ~Net();
    int connect_with_client(SOCKET &client_socket);
    int update(SOCKET client_socket, World &world);
};


#endif // NET_H
