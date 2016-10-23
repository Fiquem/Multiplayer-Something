#define _WIN32_WINNT  0x501
#define WIN32_LEAN_AND_MEAN

#include "network.h"
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 2048

int iResult, iSendResult;
int recvbuflen = DEFAULT_BUFLEN;

// let's try add multiple connections
SOCKET connections[100];
int num_connections = 0;

int init_network(){
    WSADATA wsaData;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
}

int send_message(SOCKET s, const char* m){
    iResult = send(s, m, (int) strlen(m), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }

    //printf("Bytes Sent: %ld\n", iResult);
}

int close_connection(SOCKET ConnectSocket){
    // shutdown the send half of the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
}

int client(int argc, char **argv){
    // alright let's try this again
    struct addrinfo *result = NULL,
                *ptr = NULL,
                hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[2], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by the call to getaddrinfo
    ptr=result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    int recvbuflen = DEFAULT_BUFLEN;

    char recvbuf[DEFAULT_BUFLEN];

    // Send an initial buffer
    send_message(ConnectSocket, "hello");

    //chat_message m = init_message();

    // Receive data until the server closes the connection
    do {
        memset(recvbuf, 0, sizeof(recvbuf)); // magic, got weird chars at end of string without this
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0){
            if (strcmp(recvbuf,"close") == 0) break;
            //printf("Bytes received: %d\n", iResult);
            printf("received: %s\n", recvbuf);
            char * sendbuf = getline();
            send_message(ConnectSocket, sendbuf);
            /*if (get_user_input_from_console(&m))
            {
              send_message(ConnectSocket, m.message);
              m = init_message();
            }*/
        }
    } while (strcmp(recvbuf,"close") != 0);

    printf("closing");
    close_connection(ConnectSocket);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

int server(){
        char recvbuf[DEFAULT_BUFLEN];
	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
	    printf("getaddrinfo failed: %d\n", iResult);
	    WSACleanup();
	    return 1;
	}

    SOCKET ListenSocket = INVALID_SOCKET;

    // Create a SOCKET for the server to listen for client connections

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
        printf( "Listen failed with error: %ld\n", WSAGetLastError() );
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    //SOCKET ClientSocket;

    //ClientSocket = INVALID_SOCKET;

    connections[0] = INVALID_SOCKET;

    // Accept a client socket
    /*ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }*/

    // Accept a client socket
    connections[0] = accept(ListenSocket, NULL, NULL);
    if (connections[num_connections] == INVALID_SOCKET) {
        printf("accept failed: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    num_connections++;

    // Receive until the peer shuts down the connection
    do {
        for (int i = 0; i < num_connections; i++){
        memset(recvbuf, 0, sizeof(recvbuf));
        iResult = recv(connections[i], recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            //printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            printf("received: %s\n", recvbuf);
            for (int j = 0; j < num_connections; j++)
              send_message(connections[j], recvbuf);
            //send_message(ClientSocket, "close");

            //printf("Bytes sent: %d\n", iSendResult);
        //} else
        //    printf("recv failed: %d\n", WSAGetLastError());
        }
        }
    } while (strcmp(recvbuf,"close") != 0);

    //close_connection(ClientSocket);
    for (int i = 0; i < num_connections; i++){
        close_connection(connections[i]);
        // cleanup
        closesocket(connections[i]);
    }
    WSACleanup();

    return 0;
}
