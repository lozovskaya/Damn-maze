#ifndef NET_H
#define NET_H
#include "field.h"
#include "net_includes.h"

extern char buffer[BUFF_SIZE];
extern SOCKET my_socket;

int get_data_timeout(SOCKET client_socket, char* buff, size_t len, int sec = 0, int usec = 10000);
int init_net();
int connect_with_client(SOCKET &client_socket);int update_net(SOCKET client_socket, const field &F);
#endif // NET_H
