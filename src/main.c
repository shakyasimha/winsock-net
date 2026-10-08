#include "main.h"

int main(void) {
    WSADATA wsaData; 

    // Request Winsock version 2.2
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);

    if(result!=0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }
}