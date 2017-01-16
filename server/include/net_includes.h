#ifndef NET_INCLUDES_H
#define NET_INCLUDES_H

#ifdef _WIN32
    #pragma comment ( lib, "ws2_32.lib" )

    #include <cwchar>
    #include <winsock2.h>
    #include <windows.h>

    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #define MSG_CONFIRM 0
    #define SHUT_RDWR 0

    typedef int socklen_t;
#else
    #include <netinet/in.h>
    typedef int SOCKET;
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

const static int BUFF_SIZE = 1024 * 1024;
const static short PORT = 5050;

const static int MSG_FAIL = 0;
const static int MSG_OK = 1;
const static int MSG_HELLO = 0;
const static int MSG_GET_DRAW_DATA = 1;
const static int MSG_PLAYER_MOVE = 2;


#endif // NET_INCLUDES_H
