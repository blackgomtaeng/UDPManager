#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "main.h"

int initClient(const char* serverIp, int port, struct sockaddr_in* serverAddr);
int sendData(int sock, const char* msg, struct sockaddr_in* serverAddr);
int recvData(int sock, char* buffer, int bufSize, struct sockaddr_in* serverAddr);
void closeClient(int sock);

#ifdef _WIN32
DWORD WINAPI clientThread(LPVOID args);
#else
void* clientThread(void* args);
#endif

#endif
