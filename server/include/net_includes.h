#ifndef NET_INCLUDES_H
#define NET_INCLUDES_H
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
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define BUFF_SIZE 1024
#define PORT 5050
const static int MSG_OK = 0;
const static int MSG_HELLO = 0;
const static int MSG_GET_DRAW_DATA = 1;


#endif // NET_INCLUDES_H
