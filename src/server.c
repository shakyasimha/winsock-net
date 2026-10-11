#include "server.h"

int main(void) {
    WSADATA wsaData;

    // Request winsock version 2.2
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);

    if(result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }

    // Defining server address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;            // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    serverAddr.sin_port = htons(8080);          // port 8080

    // Creating socket
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenSocket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Bind socket
    result = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(result == SOCKET_ERROR) {
        printf("Socket binding failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Listen to the socket
    result = listen(listenSocket, SOMAXCONN);
    if(result == SOCKET_ERROR) {
        printf("Socket listening failed. %d\n", result);
        WSACleanup();
        return 1;
    }

    printf("Server successfully bound and listening on http://localhost:8080.....\n");

    while(1) {
        struct sockaddr_in clientAddr;  // Defining client address
        int clientAddrLen = sizeof(clientAddr);

        SOCKET clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if(clientSocket == INVALID_SOCKET) {
            printf("Failed to accept from client socket: %d\n", WSAGetLastError());
            WSACleanup();
            continue;
        }

        printf("Client connected and listening on port 8080.....\n");

        // Return an HTTP response
        const char *http_response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: 46\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<h1>Hello from your C Winsock HTTP Server!</h1>";

        // Send the response to the client socket
        send(clientSocket, http_response, (int)strlen(http_response), 0);

        closesocket(clientSocket);
    }

    // Cleanup for now
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}