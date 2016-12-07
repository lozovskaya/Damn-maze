#include "include/net.h"
#include "include/net_includes.h"
#include "include/util.h"
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <thread>


void accept_new_clients(Net& net) {
    SOCKET client_sock;
    while (true) {
        net.connect_with_client(client_sock);
        net.clients[client_sock].socket = client_sock;
    }
}

int Net::get_data_timeout(SOCKET client_socket, size_t len, int sec, int usec) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(client_socket, &readfds);
    struct timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    if (select(client_socket + 1, &readfds, NULL, NULL, &timeout) > 0) {
        return recv(client_socket, buffer, len, MSG_CONFIRM);
    }
    return -1;
}

Net::Net() {
    buffer = new char[BUFF_SIZE];
  #ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), (WSADATA *)&buffer[0]))
    {
        throw std::runtime_error("WSAStartup error");
    }
  #endif
    my_socket = socket(AF_INET, SOCK_STREAM, 0); // you create your socket object
    if (my_socket < 0) {
        throw std::runtime_error("Error opening socket");
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
    std::thread
    accepting_thread(accept_new_clients,
    std::ref(*this));
    accepting_thread.detach();
}

Net::~Net() {
  #ifdef _WIN32
    WSACleanup();
  #endif
  delete[] buffer;
  shutdown(my_socket, SHUT_RDWR);
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


int Net::new_client(World &world) {
    char *current_ptr = buffer + 1;
    int id = world.add_player();
    buffer[0] = MSG_OK;
    write_value(&id, current_ptr);
    return current_ptr - buffer;
}

int Net::update_processing_keys(World &world) {
    char *current_ptr = buffer + 1;
    int player_id = -1;
    std::vector<int> buttons_pressed;
    write_value(&player_id, current_ptr);
    write_vector(buttons_pressed, current_ptr);
    world.change_player_state(player_id, buttons_pressed);
    buffer[0] = MSG_OK;
    return 1;
}

void Net::update_one_client(SOCKET client_socket, World &world) {
    int size = get_data_timeout(client_socket, BUFF_SIZE - 1);
    if (size <= 0) {
        return;
    }
    switch (buffer[0]) {
      case MSG_HELLO:
        printf("new client\n");
        size = new_client(world);
        break;

      case MSG_GET_DRAW_DATA:
        size = world.write_bytes(buffer);
        break;

      case MSG_PLAYER_MOVE:
        size = update_processing_keys(world);
        break;

      default:
        printf("No matches for message type");
        buffer[0] = MSG_FAIL;
        size = 1;
        break;
    }
    send(client_socket, buffer, size, MSG_CONFIRM);
}

int Net::update(World &world) {
    for (auto client : clients) {
        SOCKET client_socket = client.first;
        update_one_client(client_socket, world);
    }
    return 0;
}
