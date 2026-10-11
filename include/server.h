#ifndef SERVER_H
#define SERVER_H

// defining win32 lean and mean to prevent winsock conflicts
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Autolink winsock library for msvc compilers
// #ifndef _MSC_VER
#pragma comment(lib, "Ws2_32.lib")
// #endif 

#endif // MAIN_H