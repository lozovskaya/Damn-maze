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

#define BUFF_SIZE 256
#define PORT 5050

char buffer[BUFF_SIZE];
SOCKET my_socket;

int init_net() {
    struct sockaddr_in serv_addr;
    my_socket = socket(AF_INET, SOCK_STREAM, 0); // you create your socket object
    if (my_socket < 0) 
    {
        printf("ERROR opening socket");
        return -1;
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr)); //  Заполнить нулями байты, начиная с того, 
                                                      //  на который указывает первый параметр (указатель), 
                                                     //  и всего (второй параметр) байтов

    serv_addr.sin_family = AF_INET;                                             //
    serv_addr.sin_addr.s_addr = INADDR_ANY;                                     //
    serv_addr.sin_port = htons(PORT);                                           // just magic you have to do
    if (bind(my_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //
    {
          printf("ERROR on binding\n");
          return -1;
    }

    listen(my_socket, 5); // you are ready to connect with clients
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
}

int dial_with_client() {
    SOCKET client_socket;
    connect_with_client(client_socket);
    memset(buffer, 0, 256);
    int n = recv(client_socket, buffer, BUFF_SIZE - 1, MSG_CONFIRM); // getting data from client_socket, 
                                                           // writing it in buffer, max_amount of data is BUFF_SIZE bytes
    if (n < 0) // n - amount of bytes you just have got. if it is negative, something is bad
    {
        printf("ERROR reading from socket\n");
        return -1;
    }
    printf("Here is the message: %d %s\n", n, buffer);
    sprintf(buffer, "I got your message");
    n = send(client_socket, buffer, strlen(buffer), MSG_CONFIRM); // write to the first parameter, 
                                                                    // from second parameter, amount of bytes - third parameter
    n = recv(client_socket, buffer, BUFF_SIZE - 1, MSG_CONFIRM);
    int number;
    memcpy(&number, buffer, sizeof(int)); // Скопировать (третий аргумент) байтов из (второй аргумент) в (первый аргумент)
    printf("%d\n", number);
    number++;
    memcpy(buffer, &number, sizeof(int));
    n = send(client_socket, buffer, sizeof(int), MSG_CONFIRM);  
    if (n < 0)
    {
        printf("ERROR writing to socket\n");
        return -1;
    }
    shutdown(client_socket, SHUT_RDWR);
}

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
