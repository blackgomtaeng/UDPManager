#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "main.h"

int initServer(int port, const char* ip);
int recvData(int sock, char* buffer, int bufSize, struct sockaddr_in* clientAddr);
int sendData(int sock, const char* msg, struct sockaddr_in* clientAddr);
void closeServer(int sock);

#ifdef _WIN32
    DWORD WINAPI serverThread(LPVOID args);
#else
    void* serverThread(void* args);
#endif

#endif
