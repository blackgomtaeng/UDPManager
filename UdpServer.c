#include "UdpServer.h"

int initServer(int port, const char* ip) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = ip ? inet_addr(ip) : INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(1);
    }
    return sock;
}

int recvData(int sock, char* buffer, int bufSize, struct sockaddr_in* clientAddr) {
    socklen_t len = sizeof(*clientAddr);
    return recvfrom(sock, buffer, bufSize, 0, (struct sockaddr*)clientAddr, &len);
}

int sendData(int sock, const char* msg, struct sockaddr_in* clientAddr) {
    return sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)clientAddr, sizeof(*clientAddr));
}

void closeServer(int sock) {
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

#ifdef _WIN32
DWORD WINAPI serverThread(LPVOID args) {
#else
void* serverThread(void* args) {
#endif
    int sock = *(int*)args;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in clientAddr;

    while (1) {
        int n = recvData(sock, buffer, sizeof(buffer), &clientAddr);
        buffer[n] = '\0';
        printf("Server received: %s\n", buffer);
        sendData(sock, "ACK from server", &clientAddr);
    }
    return 0;
}
