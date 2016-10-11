#ifdef _WIN32
	#pragma comment ( lib, "ws2_32.lib" )
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#define MSG_CONFIRM 0
	#define SHUT_RDWR 0
	#include <winsock2.h>
	#include <windows.h>
	typedef int socklen_t;
#else
	#include <netinet/in.h> // all socket functions
    typedef int SOCKET;
#endif
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define BUFF_SIZE 1024
#define PORT 5050

char buffer[BUFF_SIZE];
SOCKET my_socket;

int get_data_timeout(SOCKET client_socket, char* buff, size_t len, int sec = 0, int usec = 100) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(client_socket, &readfds);
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;

    if (select(my_socket, &readfds, NULL, NULL, &timeout) > 0) {
        return recv(my_socket, buff, len, MSG_CONFIRM);
    }
    return -1;
}

int init_net() {
    struct sockaddr_in serv_addr;
    my_socket = socket(AF_INET, SOCK_STREAM, 0); // you create your socket object
    if (my_socket < 0) 
    {
        printf("ERROR opening socket");
        return -1;
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    int i = 0;
    while (bind(my_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        i++;
        serv_addr.sin_port = htons(PORT + i);
    }
    printf("port = %d\n", PORT + i);
    listen(my_socket, 5);
    return 0;
}

int connect_with_client(SOCKET &client_socket) {
    socklen_t client_length;
    struct sockaddr_in client_addr;
    client_length = sizeof(client_addr);
    client_socket = accept(my_socket, (struct sockaddr *) &client_addr, &client_length); 
                            // at previous line you wait until one client connects with you
    if (client_socket < 0)
    {
        printf("ERROR on accept\n");
        return -1;
    }

    return 0;
}

int update_net(SOCKET client_socket, const field &F) {
    printf("wait\n");
    int size = recv(client_socket, buffer, BUFF_SIZE - 1, MSG_CONFIRM);
    printf("get %d\n", size);
    if (size <= 0) {
        return 0;
    }
    if (buffer[0] == 1) {
        printf("send\n");
        size = F.write_bytes(buffer);
        send(client_socket, buffer, size, MSG_CONFIRM);
    }
    return 0;
}
/*
int main()
{
    if (init_net()) {
        printf("failed in init_net\n");
        return 0;
    }
    if (dial_with_client()) {
        printf("failed in dial_with_client\n");
        return 0;
    }
    shutdown(my_socket, SHUT_RDWR);
    return 0; 
}
*/
