#ifndef NET_H
#define NET_H
#include "world.h"
#include "net_includes.h"

class Net {
    SOCKET my_socket;
    char buffer[BUFF_SIZE];
    int get_data_timeout(SOCKET client_socket, char* buff, size_t len, int sec = 0, int usec = 10000);
  public:
    Net();
    ~Net();
    int connect_with_client(SOCKET &client_socket);
    int update(SOCKET client_socket, World &world);
};


#endif // NET_H
