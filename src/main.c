#include <winsock.h>
#include "stdio.h"

int main() {
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}
}