#include "UdpClient.h"

int initClient(const char* serverIp, int port, struct sockaddr_in* serverAddr) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    memset(serverAddr, 0, sizeof(*serverAddr));
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(port);
    serverAddr->sin_addr.s_addr = inet_addr(serverIp);

    return sock;
}

int sendData(int sock, const char* msg, struct sockaddr_in* serverAddr) {
    return sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)serverAddr, sizeof(*serverAddr));
}

int recvData(int sock, char* buffer, int bufSize, struct sockaddr_in* serverAddr) {
    socklen_t len = sizeof(*serverAddr);
    return recvfrom(sock, buffer, bufSize, 0, (struct sockaddr*)serverAddr, &len);
}

void closeClient(int sock) {
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

#ifdef _WIN32
DWORD WINAPI clientThread(LPVOID args) {
#else
void* clientThread(void* args) {
#endif
    SocketInfo* info = (SocketInfo*)args;
    char buffer[BUFFER_SIZE];

    while (1) {
        sendData(info->sock, "Hello from client", &info->addr);
        int n = recvData(info->sock, buffer, sizeof(buffer), &info->addr);
        buffer[n] = '\0';
        printf("Client received: %s\n", buffer);
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }
    return 0;
}
