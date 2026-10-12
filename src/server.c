#include "server.h"

#define BUF_SIZE 4096


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

        // This is where the HTTP requests are handled
        char buffer[BUF_SIZE] = {0};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        // Checking if bytes have been received or not
        if(bytesReceived <= 0) {
            closesocket(clientSocket);
            continue;
        }

        // Handling GET request
        if(strncmp(buffer, "GET", 3) == 0) {
            if(strncmp(buffer, "GET / ", 6) == 0 || strncmp(buffer, "GET /HTTP", 9) == 0) {
                const char *home_response = 
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "Content-Length: 46\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<h1>Hello from your C Winsock HTTP Server!</h1>\r\n";

                send(clientSocket, home_response, (int)strlen(home_response), 0);
            }
            else {
                // -- 404 NOT FOUND ERROR -- 
                const char* not_found = 
                    "HTTP/1.1 404 NOT FOUND\r\r"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "Content-Length: 46\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "<h1>404 Page Not Found</h1>\r\n";

                send(clientSocket, not_found, (int)strlen(not_found), 0);
            }
        }

        // Handling post request
        if(strncmp(buffer, "POST", 4) == 0) {
            char *payload = strstr(buffer, "\r\n\r\n");

            if (payload != NULL) {
                payload += 4;
                // int payload_len = (int)strlen(payload);

                const char *post_response = 
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "Content-Length: 46\r\n"
                    "Connection: close\r\n"
                    "\r\n";

                send(clientSocket, post_response, (int)strlen(post_response), 0);
                send(clientSocket, payload, (int)strlen(payload), 0);   // Echo back the payload 
            } else {
                const char *post_response = 
                    "HTTP/1.1 400 BAD REQUEST\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "Content-Length: 46\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "No payload found.\r\n";
                
                send(clientSocket, post_response, (int)strlen(post_response), 0);
            }
        } 

        closesocket(clientSocket);
    }


    // Cleanup for now
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}