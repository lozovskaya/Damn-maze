#include "include/net.h"
#include "include/net_includes.h"
#include <cstdio>
#include <stdexcept>


int Net::get_data_timeout(SOCKET client_socket, char* buff, size_t len, int sec, int usec) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(client_socket, &readfds);
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    if (select(client_socket + 1, &readfds, NULL, NULL, &timeout) > 0) {
        return recv(client_socket, buff, len, MSG_CONFIRM);
    }
    return -1;
}

Net::Net() {
  #ifdef _WIN32
	if (WSAStartup(MAKEWORD(2, 2), (WSADATA *)&buffer[0]))
	{
		sprintf(buffer, "WSAStartup error %d\n", WSAGetLastError());
        throw std::runtime_error(buffer);
	}
  #endif
    my_socket = socket(AF_INET, SOCK_STREAM, 0); // you create your socket object
    if (my_socket < 0) {
        sprintf(buffer, "ERROR opening socket");
        throw std::runtime_error(buffer);
    }
    sockaddr_in serv_addr;
    memset((char *) &serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    int i = 0;
    while (bind(my_socket, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        i++;
        serv_addr.sin_port = htons(PORT + i);
    }
    printf("port = %d\n", PORT + i);
    listen(my_socket, 5);
}

Net::~Net() {
  #ifdef _WIN32
    WSACleanup();
  #endif
  close(my_socket);
}

int Net::connect_with_client(SOCKET &client_socket) {
    socklen_t client_length;
    struct sockaddr_in client_addr;
    client_length = sizeof(client_addr);
    client_socket = accept(my_socket, (struct sockaddr *) &client_addr, &client_length); 
                            // at previous line you wait until one client connects with you
    if (client_socket < 0) {
        printf("ERROR on accept\n");
        return -1;
    }
    return 0;
}

int Net::update(SOCKET client_socket, World &world) {
    printf("wait\n");
    int size = get_data_timeout(client_socket, buffer, BUFF_SIZE - 1);
    printf("get %d\n", size);
    if (size <= 0) {
        return 0;
    }
    int id = -1;
    switch (buffer[0]) {
      case MSG_HELLO:
        printf("new client\n");
        id = world.add_player();
        buffer[0] = MSG_OK;
        memcpy(buffer + 1, &id, sizeof(int));
        send(client_socket, buffer, 1 + sizeof(int), MSG_CONFIRM);
        break;
      case MSG_GET_DRAW_DATA:
        printf("send\n");
        size = world.write_bytes(buffer);
        send(client_socket, buffer, size, MSG_CONFIRM);
        break;
    }
    return 0;
}
