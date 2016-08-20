// using https://msdn.microsoft.com/en-us/library/windows/desktop/ms738566(v=vs.85).aspx
#pragma once

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

int client(int argc, char **argv);
int server();