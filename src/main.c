// started 19/08/16
// using http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT "3490"

int main() {
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}

	int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa; // WHY DOESN'T THIS WORK I DON'T UNDERSTAND NETWORKING AT ALL I AM DONE
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
}