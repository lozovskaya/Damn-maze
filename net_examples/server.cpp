/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <cstdio> //printf
#include <cstring> //memcpy
#include <iostream>
#include <cstdlib>
//#include <cunistd> //read write functions
#include <netinet/in.h> // all socket functions
#ifndef _WIN32
    typedef int SOCKET;
#endif


#define PORT 5050

int main()
{
     SOCKET my_socket, client_socket;
     socklen_t client_length;
     char buffer[256];
     struct sockaddr_in serv_addr, client_addr;
     my_socket = socket(AF_INET, SOCK_STREAM, 0); // you create your socket object
     if (my_socket < 0) 
     {
        printf("ERROR opening socket");
        return 0;
     }
     memset((char *) &serv_addr, 0, sizeof(serv_addr)); //  Заполнить нулями байты, начиная с того, 
//                                                  //  на который указывает первый параметр (указатель), 
                                                    //  и всего (второй параметр) байтов
     
     serv_addr.sin_family = AF_INET;                                             //
     serv_addr.sin_addr.s_addr = INADDR_ANY;                                     //
     serv_addr.sin_port = htons(PORT);                                           // just magic you have to do
     if (bind(my_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //
     {
              printf("ERROR on binding\n");
              return 0;
     }
     
     listen(my_socket, 5); // you are ready to connect with clients
     client_length = sizeof(client_addr);
     client_socket = accept(my_socket, (struct sockaddr *) &client_addr, &client_length); // here you wait until one client connects with you
     
     if (client_socket < 0)
     {
          printf("ERROR on accept\n");
          return 0;
     }
     memset(buffer, 0, 256);
     int n = recv(client_socket, buffer, 255, MSG_CONFIRM); // getting data from client_socket, writing it in buffer, max_amount of data is 255 bytes
     if (n < 0) // n - amount of bytes you just have got. if it is negative, something is bad
     {
         printf("ERROR reading from socket\n");
         return 0;
     }
     printf("Here is the message: %d %s\n", n, buffer);
     n = send(client_socket, "I got your message", 18, MSG_CONFIRM); // write to the first parameter, from second parameter, amount of bytes - third parameter
     n = recv(client_socket, buffer, 255, MSG_CONFIRM);
     int number;
     memcpy(&number, buffer, 4); // Скопировать (третий аргумент) байтов из (второй аргумент) в (первый аргумент)
     printf("%d\n", number);
     number++;
     memcpy(buffer, &number, 4);
     n = send(client_socket, buffer, 4, MSG_CONFIRM);  
     if (n < 0)
     {
        printf("ERROR writing to socket\n");
        return 0;
     }
     shutdown(client_socket, SHUT_RDWR);
     shutdown(my_socket, SHUT_RDWR);
     return 0; 
}
