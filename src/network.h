// using https://msdn.microsoft.com/en-us/library/windows/desktop/ms738566(v=vs.85).aspx
#pragma once

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int init_network();
int client(int argc, char **argv);
int server();
int send_message(SOCKET ConnectSocket, const char* message);
int close_connection(SOCKET ConnectSocket);