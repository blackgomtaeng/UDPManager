#include "main.h"
#include "UdpServer.h"
#include "UdpClient.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [server|client] <ip> <port>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "server") == 0) {
        int port = atoi(argv[3]);
        int sock = initServer(port, argv[2]);

#ifdef _WIN32
        HANDLE hThread = CreateThread(NULL, 0, serverThread, &sock, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
#else
        pthread_t tid;
        pthread_create(&tid, NULL, serverThread, &sock);
        pthread_join(tid, NULL);
#endif

        closeServer(sock);
    } else if (strcmp(argv[1], "client") == 0) {
        int port = atoi(argv[3]);
        struct sockaddr_in serverAddr;
        int sock = initClient(argv[2], port, &serverAddr);

        SocketInfo info = { sock, serverAddr };

#ifdef _WIN32
        HANDLE hThread = CreateThread(NULL, 0, clientThread, &info, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
#else
        pthread_t tid;
        pthread_create(&tid, NULL, clientThread, &info);
        pthread_join(tid, NULL);
#endif

        closeClient(sock);
    } else {
        printf("Invalid mode. Use 'server' or 'client'.\n");
    }

    return 0;
}
