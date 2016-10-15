#include "net_includes.h"

char buffer[BUFF_SIZE];
SOCKET my_socket;

int get_data_timeout(SOCKET client_socket, char* buff, size_t len, int sec = 0, int usec = 10000) {
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

int init_net() {
    struct sockaddr_in serv_addr;
    my_socket = socket(AF_INET, SOCK_STREAM, 0); // you create your socket object
    if (my_socket < 0) {
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
    if (client_socket < 0) {
        printf("ERROR on accept\n");
        return -1;
    }
    return 0;
}

int update_net(SOCKET client_socket, const field &F) {
    printf("wait\n");
    int size = get_data_timeout(client_socket, buffer, BUFF_SIZE - 1);
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