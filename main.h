#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <pthread.h>
#endif

#define BUFFER_SIZE 1024 // 공통 버퍼 크기


typedef struct           // 공통 구조체 예시
{
    int sock;
    struct sockaddr_in addr;
} SocketInfo;

#endif
